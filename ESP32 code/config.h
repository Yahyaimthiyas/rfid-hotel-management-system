/**
 * @file config.h
 * @brief ESP32 Configuration Header for RFID Hotel Management System
 * @author Hardware Team
 * @version 1.0.0
 * @date 2024
 * 
 * @section config_overview Configuration Overview
 * 
 * This header file contains all configuration parameters for the ESP32 RFID
 * reader system. Update these values according to your specific deployment.
 */

#ifndef CONFIG_H
#define CONFIG_H

// ============================================================================
// WIFI CONFIGURATION
// ============================================================================

/**
 * @brief WiFi network credentials
 * @warning Update these values for your network
 */
#define WIFI_SSID "OPPO"
#define WIFI_PASSWORD "123456789"
#define WIFI_TIMEOUT 15000          ///< WiFi connection timeout (ms)
#define WIFI_RETRY_DELAY 500        ///< Delay between connection attempts (ms)

// ============================================================================
// SERVER CONFIGURATION
// ============================================================================

/**
 * @brief Backend server configuration
 * @param WEBSOCKET_HOST Backend server hostname
 * @param WEBSOCKET_PORT HTTPS port (443 for SSL)
 * @param WEBSOCKET_PATH MQTT WebSocket endpoint
 */
#define WEBSOCKET_HOST "coastal-grand-back.onrender.com"
#define WEBSOCKET_PORT 443
#define WEBSOCKET_PATH "/mqtt"
#define WEBSOCKET_PROTOCOL "wss"

// ============================================================================
// ROOM CONFIGURATION
// ============================================================================

/**
 * @brief Room identification parameters
 * @warning CHANGE THESE VALUES FOR EACH ESP32 DEVICE
 * 
 * @param ROOM_NUMBER Physical room number (e.g., "101", "202", "305")
 * @param BUILDING_ID Building identifier (usually "main")
 * @param FLOOR_NUMBER Floor/Hotel ID - Maps to backend hotelId (1-8)
 * 
 * Hotel ID Mapping:
 * 1 = Coastal Grand Hotel - Ooty
 * 2 = Coastal Grand Hotel - Salem  
 * 3 = Coastal Grand Hotel - Yercaud
 * 4 = Coastal Grand Hotel - Puducherry
 * 5 = Coastal Grand Hotel - Namakkal
 * 6 = Coastal Grand Hotel - Chennai
 * 7 = Coastal Grand Hotel - Bangalore
 * 8 = Coastal Grand Hotel - Kotagiri
 */
#define ROOM_NUMBER "202"           ///< Change this for each room
#define BUILDING_ID "main"          ///< Building identifier
#define FLOOR_NUMBER "3"            ///< Hotel ID (1-8) - Currently Yercaud
#define HOTEL_NAME "Coastal Grand Hotel - Yercaud"

// ============================================================================
// HARDWARE PIN CONFIGURATION
// ============================================================================

/**
 * @brief ESP32 GPIO pin assignments
 * @details MFRC522 RFID Reader connections
 * 
 * Pin Mapping:
 * MFRC522    ESP32
 * --------   -----
 * RST        GPIO 22
 * SDA(SS)    GPIO 21
 * MOSI       GPIO 23 (default SPI)
 * MISO       GPIO 19 (default SPI)
 * SCK        GPIO 18 (default SPI)
 * 3.3V       3.3V
 * GND        GND
 */
#define RFID_RST_PIN 22             ///< Reset pin for MFRC522
#define RFID_SS_PIN 21              ///< Slave Select pin for MFRC522
#define LED_PIN 2                   ///< Built-in LED pin
#define BUZZER_PIN 4                ///< Buzzer pin (optional)

// ============================================================================
// RFID CONFIGURATION
// ============================================================================

/**
 * @brief RFID system parameters
 */
#define CARD_ABSENT_THRESHOLD 5     ///< Readings before considering card absent
#define CARD_READ_DELAY 100         ///< Delay between RFID readings (ms)
#define MAX_USERS 50                ///< Maximum number of authorized users

// ============================================================================
// NTP TIME CONFIGURATION
// ============================================================================

/**
 * @brief Network Time Protocol configuration
 * @param GMT_OFFSET_SEC Timezone offset in seconds (IST = +5:30 = 19800)
 */
#define NTP_SERVER1 "pool.ntp.org"
#define NTP_SERVER2 "time.nist.gov"
#define NTP_SERVER3 "time.google.com"
#define GMT_OFFSET_SEC 19800        ///< IST +5:30 hours in seconds
#define DAYLIGHT_OFFSET_SEC 0       ///< Daylight saving offset
#define NTP_SYNC_INTERVAL 3600000   ///< Time sync interval (1 hour)

// ============================================================================
// WEBSOCKET CONFIGURATION
// ============================================================================

/**
 * @brief WebSocket connection parameters
 */
#define WS_RECONNECT_INTERVAL 5000  ///< Reconnection attempt interval (ms)
#define WS_HEARTBEAT_INTERVAL 15000 ///< Heartbeat ping interval (ms)
#define WS_HEARTBEAT_TIMEOUT 3000   ///< Heartbeat timeout (ms)
#define WS_MAX_RETRY_COUNT 2        ///< Maximum reconnection attempts

// ============================================================================
// DEBUG CONFIGURATION
// ============================================================================

/**
 * @brief Debug and logging configuration
 */
#define DEBUG_MODE true             ///< Enable debug output
#define SERIAL_BAUD_RATE 115200     ///< Serial communication baud rate
#define DEBUG_RFID false            ///< Enable RFID debug messages
#define DEBUG_WEBSOCKET true        ///< Enable WebSocket debug messages
#define DEBUG_MQTT true             ///< Enable MQTT debug messages

// ============================================================================
// DEVICE IDENTIFICATION
// ============================================================================

/**
 * @brief Device identification parameters
 */
#define DEVICE_ID "ESP32_ROOM_" ROOM_NUMBER "_HOTEL_" FLOOR_NUMBER
#define FIRMWARE_VERSION "1.0.0"
#define DEVICE_TYPE "RFID_READER"

// ============================================================================
// SECURITY CONFIGURATION
// ============================================================================

/**
 * @brief Security settings
 */
#define ENABLE_ENCRYPTION false     ///< Enable data encryption (future use)
#define MAX_FAILED_ATTEMPTS 5       ///< Max failed card attempts before alert

// ============================================================================
// MQTT TOPIC CONFIGURATION
// ============================================================================

/**
 * @brief MQTT topic structure
 * @details Topics follow the pattern: campus/room/{building}/{floor}/{room}/{type}
 * 
 * Topic Types:
 * - attendance: Check-in/check-out events
 * - alerts: Security alerts and warnings
 * - denied_access: Unauthorized access attempts
 */
#define MQTT_TOPIC_BASE "campus/room"
#define MQTT_QOS 0                  ///< MQTT Quality of Service level
#define MQTT_RETAIN false           ///< MQTT retain flag

// ============================================================================
// PERFORMANCE CONFIGURATION
// ============================================================================

/**
 * @brief Performance and timing parameters
 */
#define MAIN_LOOP_DELAY 100         ///< Main loop delay (ms)
#define WATCHDOG_TIMEOUT 30000      ///< Watchdog timer timeout (ms)
#define MEMORY_CHECK_INTERVAL 60000 ///< Memory usage check interval (ms)

// ============================================================================
// ERROR HANDLING
// ============================================================================

/**
 * @brief Error handling configuration
 */
#define MAX_ERROR_COUNT 10          ///< Maximum consecutive errors before reset
#define ERROR_RESET_DELAY 5000      ///< Delay before error reset (ms)

// ============================================================================
// FEATURE FLAGS
// ============================================================================

/**
 * @brief Feature enable/disable flags
 */
#define ENABLE_BUZZER false         ///< Enable buzzer feedback
#define ENABLE_LED_FEEDBACK true    ///< Enable LED status indicators
#define ENABLE_DEEP_SLEEP false     ///< Enable deep sleep mode (not recommended)
#define ENABLE_OTA_UPDATES false    ///< Enable Over-The-Air updates

// ============================================================================
// VALIDATION MACROS
// ============================================================================

/**
 * @brief Compile-time validation
 */
#if !defined(ROOM_NUMBER) || !defined(FLOOR_NUMBER)
#error "ROOM_NUMBER and FLOOR_NUMBER must be defined"
#endif

#if !defined(WIFI_SSID) || !defined(WIFI_PASSWORD)
#error "WiFi credentials must be defined"
#endif

#if CARD_ABSENT_THRESHOLD < 1 || CARD_ABSENT_THRESHOLD > 20
#error "CARD_ABSENT_THRESHOLD must be between 1 and 20"
#endif

// ============================================================================
// HELPER MACROS
// ============================================================================

/**
 * @brief Utility macros for common operations
 */
#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

/**
 * @brief Debug print macro
 */
#if DEBUG_MODE
#define DEBUG_PRINT(x) Serial.print(x)
#define DEBUG_PRINTLN(x) Serial.println(x)
#define DEBUG_PRINTF(format, ...) Serial.printf(format, ##__VA_ARGS__)
#else
#define DEBUG_PRINT(x)
#define DEBUG_PRINTLN(x)
#define DEBUG_PRINTF(format, ...)
#endif

/**
 * @brief Memory usage reporting
 */
#define REPORT_MEMORY() do { \
    if (DEBUG_MODE) { \
        DEBUG_PRINTF("Free heap: %d bytes\n", ESP.getFreeHeap()); \
    } \
} while(0)

#endif // CONFIG_H

/**
 * @example Configuration Examples
 * 
 * Room 101, Hotel 1 (Ooty):
 * #define ROOM_NUMBER "101"
 * #define FLOOR_NUMBER "1"
 * 
 * Room 205, Hotel 2 (Salem):
 * #define ROOM_NUMBER "205"
 * #define FLOOR_NUMBER "2"
 * 
 * Room 312, Hotel 3 (Yercaud):
 * #define ROOM_NUMBER "312"
 * #define FLOOR_NUMBER "3"
 */