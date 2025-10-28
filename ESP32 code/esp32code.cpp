#include <SPI.h>
#include <MFRC522.h>
#include <WiFi.h>
#include <WebSocketsClient.h>
#include <ArduinoJson.h>
#include "time.h"
#include "config.h"

// ---- Pins and Config ----
#define RST_PIN RFID_RST_PIN
#define SS_PIN RFID_SS_PIN

const char* ssid = WIFI_SSID;
const char* password = WIFI_PASSWORD;

// WebSocket MQTT connection (from config.h)
const char* websocketHost = WEBSOCKET_HOST;
const int   websocketPort = WEBSOCKET_PORT;
const char* websocketPath = WEBSOCKET_PATH;

const char* roomNumber  = ROOM_NUMBER;
const char* building    = BUILDING_ID;
const char* floorNumber = FLOOR_NUMBER;

// ---- NTP Config (from config.h) ----
const char* ntpServer1       = NTP_SERVER1;
const char* ntpServer2       = NTP_SERVER2;
const char* ntpServer3       = NTP_SERVER3;
const long  gmtOffset_sec    = GMT_OFFSET_SEC;
const int   daylightOffset_sec = DAYLIGHT_OFFSET_SEC;
unsigned long lastSyncAttempt    = 0;
const unsigned long SYNC_INTERVAL = NTP_SYNC_INTERVAL;

// ---- RFID/WebSocket objects ----
MFRC522 mfrc522(SS_PIN, RST_PIN);
WebSocketsClient webSocket;

// ---- UIDs and Roles ----
struct UserAuth {
  byte uid[4];
  const char* role;
};

UserAuth users[] = {
  {{0xAF, 0x4D, 0x99, 0x1F}, "Maintenance"},
  {{0xBF, 0xD1, 0x07, 0x1F}, "Manager"},
  {{0xB2, 0xF9, 0x7C, 0x00}, "Guest"}
};
const int numUsers = sizeof(users) / sizeof(users[0]);

// ---- Presence Detection State ----
byte         presentCardUID[4] = {0};
int          presentUserIndex  = -1;
unsigned long checkedInTime    = 0;
bool         checkedIn         = false;
int          cardAbsentCount   = 0;
const int    CARD_ABSENT_THRESHOLD = 5;
bool         websocketConnected = false;

// ---- Function prototypes ----
void setupSystem();
void connectWiFi();
bool syncTime();
String getTimestamp();
int  getUserIndex(byte *uid, byte length);
void cleanupRFID();
void connectWebSocket();
void publishToMQTT(const char* type, const char* jsonData);
bool isCardPresent();
void webSocketEvent(WStype_t type, uint8_t * payload, size_t length);
void handleUnauthorizedAccess(const char* cardUID);

void setup() {
  Serial.begin(115200);
  delay(100);
  SPI.begin();
  mfrc522.PCD_Init();
  
  // Setup WebSocket event handler
  webSocket.onEvent(webSocketEvent);
  
  setupSystem();
}

void loop() {
  // Maintain connections
  if (WiFi.status() != WL_CONNECTED) {
    connectWiFi();
  }
  
  if (!websocketConnected) {
    connectWebSocket();
  }
  
  webSocket.loop();

  // Periodic time sync
  if (millis() - lastSyncAttempt > SYNC_INTERVAL) {
    if (WiFi.status() == WL_CONNECTED && syncTime()) {
      lastSyncAttempt = millis();
    }
  }

  // ---- Continuous Card Presence Detection ----
  if (isCardPresent()) {
    cardAbsentCount = 0;

    if (!checkedIn) {
      int userIdx = getUserIndex(mfrc522.uid.uidByte, mfrc522.uid.size);
      
      char cardUID[9];
      snprintf(cardUID, sizeof(cardUID),
               "%02X%02X%02X%02X",
               mfrc522.uid.uidByte[0],
               mfrc522.uid.uidByte[1],
               mfrc522.uid.uidByte[2],
               mfrc522.uid.uidByte[3]);

      if (userIdx != -1) {
        // Authorized user - check in
        String role = users[userIdx].role;
        
        DynamicJsonDocument doc(512);
        doc["card_uid"] = cardUID;
        doc["role"] = role;
        doc["check_in"] = getTimestamp();
        doc["room"] = roomNumber;
        
        String jsonString;
        serializeJson(doc, jsonString);
        
        publishToMQTT("attendance", jsonString.c_str());
        Serial.printf("%s Checked IN at %s\n", role.c_str(), getTimestamp().c_str());

        memcpy(presentCardUID, mfrc522.uid.uidByte, 4);
        presentUserIndex = userIdx;
        checkedInTime = millis();
        checkedIn = true;
      } else {
        // Unauthorized access attempt
        handleUnauthorizedAccess(cardUID);
      }
    }
  } else {
    cardAbsentCount++;

    if (checkedIn && cardAbsentCount >= CARD_ABSENT_THRESHOLD) {
      if (presentUserIndex != -1) {
        String role = users[presentUserIndex].role;
        unsigned long duration = (millis() - checkedInTime) / 1000;
        
        char cardUID[9];
        snprintf(cardUID, sizeof(cardUID),
                 "%02X%02X%02X%02X",
                 presentCardUID[0],
                 presentCardUID[1],
                 presentCardUID[2],
                 presentCardUID[3]);

        DynamicJsonDocument doc(512);
        doc["card_uid"] = cardUID;
        doc["role"] = role;
        doc["check_out"] = getTimestamp();
        doc["duration"] = duration;
        doc["room"] = roomNumber;
        
        String jsonString;
        serializeJson(doc, jsonString);
        
        publishToMQTT("attendance", jsonString.c_str());
        Serial.printf("%s Checked OUT at %s (duration: %lu seconds)\n",
                      role.c_str(), getTimestamp().c_str(), duration);
      }

      // Reset state
      checkedIn = false;
      presentUserIndex = -1;
      checkedInTime = 0;
      memset(presentCardUID, 0, sizeof(presentCardUID));
      cardAbsentCount = 0;
    }
  }

  delay(100);
}

void handleUnauthorizedAccess(const char* cardUID) {
  DynamicJsonDocument doc(512);
  doc["card_uid"] = cardUID;
  doc["role"] = "Unknown";
  doc["denial_reason"] = "Unauthorized card";
  doc["attempted_at"] = getTimestamp();
  doc["room"] = roomNumber;
  
  String jsonString;
  serializeJson(doc, jsonString);
  
  publishToMQTT("denied_access", jsonString.c_str());
  Serial.printf("DENIED ACCESS: Unknown card %s at %s\n", cardUID, getTimestamp().c_str());
  
  // Also send security alert
  DynamicJsonDocument alertDoc(512);
  alertDoc["card_uid"] = cardUID;
  alertDoc["role"] = "Security";
  alertDoc["alert_message"] = "Unauthorized access attempt detected";
  alertDoc["triggered_at"] = getTimestamp();
  alertDoc["room"] = roomNumber;
  
  String alertString;
  serializeJson(alertDoc, alertString);
  
  publishToMQTT("alerts", alertString.c_str());
}

bool isCardPresent() {
  byte bufferATQA[2];
  byte bufferSize = sizeof(bufferATQA);

  MFRC522::StatusCode result = mfrc522.PICC_REQA_or_WUPA(
    MFRC522::PICC_CMD_WUPA, bufferATQA, &bufferSize);

  if (result == MFRC522::STATUS_OK) {
    if (mfrc522.PICC_ReadCardSerial()) {
      return true;
    }
  }

  mfrc522.PICC_HaltA();
  return false;
}

void setupSystem() {
  Serial.println();
  connectWiFi();
  
  while (!syncTime()) {
    Serial.println("NTP sync failed, retrying in 5s...");
    delay(5000);
    if (WiFi.status() != WL_CONNECTED) connectWiFi();
  }
  
  lastSyncAttempt = millis();
  connectWebSocket();
  
  Serial.println("\n====================");
  Serial.printf("Room %s Access Control System\n", roomNumber);
  Serial.printf("Hotel ID: %s\n", floorNumber);
  Serial.printf("WebSocket: wss://%s%s\n", websocketHost, websocketPath);
  Serial.println("====================\n");
  Serial.println("Ready to read cards...");
}

void connectWiFi() {
  if (WiFi.status() == WL_CONNECTED) return;
  
  Serial.printf("Connecting to WiFi: %s\n", ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  
  unsigned long start = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - start < 15000) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println();
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("WiFi Connected! IP: " + WiFi.localIP().toString());
  } else {
    Serial.println("WiFi Connection Failed");
  }
}

bool syncTime() {
  if (WiFi.status() != WL_CONNECTED) return false;
  
  configTime(gmtOffset_sec, daylightOffset_sec,
             ntpServer1, ntpServer2, ntpServer3);
  
  Serial.print("Syncing NTP time");
  time_t now = time(nullptr);
  int attempts = 0;
  
  while (now < 8 * 3600 * 2 && attempts < 20) {
    delay(500);
    Serial.print(".");
    now = time(nullptr);
    attempts++;
  }
  
  Serial.println();
  if (attempts >= 20) return false;
  
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) return false;
  
  char buf[20];
  strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &timeinfo);
  Serial.printf("Current Time: %s\n", buf);
  return true;
}

String getTimestamp() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) return "1970-01-01 00:00:00";
  
  char buf[20];
  strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &timeinfo);
  return String(buf);
}

int getUserIndex(byte *uid, byte length) {
  if (length != 4) return -1;
  
  for (int i = 0; i < numUsers; i++) {
    if (memcmp(uid, users[i].uid, 4) == 0) return i;
  }
  return -1;
}

void cleanupRFID() {
  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();
}

void connectWebSocket() {
  if (websocketConnected) return;
  
  Serial.printf("Connecting to WebSocket: wss://%s:%d%s\n", 
                websocketHost, websocketPort, websocketPath);
  
  // Use SSL for secure connection to your Render deployment
  webSocket.beginSSL(websocketHost, websocketPort, websocketPath);
  
  // Set reconnect interval
  webSocket.setReconnectInterval(5000);
  
  // Enable heartbeat
  webSocket.enableHeartbeat(15000, 3000, 2);
}

void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {
  switch(type) {
    case WStype_DISCONNECTED:
      Serial.println("WebSocket Disconnected");
      websocketConnected = false;
      break;
      
    case WStype_CONNECTED:
      Serial.printf("WebSocket Connected to: %s\n", payload);
      websocketConnected = true;
      break;
      
    case WStype_TEXT:
      Serial.printf("Received: %s\n", payload);
      break;
      
    case WStype_ERROR:
      Serial.printf("WebSocket Error: %s\n", payload);
      websocketConnected = false;
      break;
      
    case WStype_PONG:
      Serial.println("WebSocket Pong received");
      break;
      
    default:
      break;
  }
}

void publishToMQTT(const char* type, const char* jsonData) {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Cannot publish: WiFi disconnected");
    return;
  }
  
  if (!websocketConnected) {
    Serial.println("Cannot publish: WebSocket disconnected");
    connectWebSocket();
    return;
  }

  // Create MQTT topic that matches your backend expectation
  char topic[128];
  snprintf(topic, sizeof(topic),
           "campus/room/%s/%s/%s/%s",
           building, floorNumber, roomNumber, type);

  // Create MQTT publish message
  DynamicJsonDocument mqttDoc(1024);
  mqttDoc["cmd"] = "publish";
  mqttDoc["topic"] = topic;
  mqttDoc["payload"] = jsonData;
  mqttDoc["qos"] = 0;
  mqttDoc["retain"] = false;
  
  String mqttMessage;
  serializeJson(mqttDoc, mqttMessage);
  
  // Send via WebSocket
  bool success = webSocket.sendTXT(mqttMessage);
  
  if (success) {
    Serial.printf("Published to %s: %s\n", topic, jsonData);
  } else {
    Serial.printf("Publish failed to %s\n", topic);
  }
}