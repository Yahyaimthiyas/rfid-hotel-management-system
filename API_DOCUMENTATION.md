/**
 * @file API_DOCUMENTATION.md
 * @brief Complete API Documentation for RFID Hotel Management System
 * @author Development Team
 * @version 1.0.0
 * @date December 2024
 * 
 * @section api_overview API Overview
 * 
 * This document provides comprehensive documentation for all API endpoints,
 * WebSocket events, MQTT topics, and real-time communication protocols
 * used in the RFID Hotel Management System.
 * 
 * @section base_urls Base URLs
 * - Production: https://coastal-grand-back.onrender.com
 * - Development: http://localhost:3000
 * 
 * @section authentication Authentication
 * All API endpoints require JWT authentication via Bearer token.
 */

# 📡 RFID Hotel Management System - API Documentation

## 🌐 **Base URLs**

| Environment | URL | Status |
|-------------|-----|--------|
| **Production** | `https://coastal-grand-back.onrender.com` | ✅ Live |
| **Development** | `http://localhost:3000` | 🔧 Local |

---

## 🔐 **Authentication**

### **JWT Token Authentication**

All API endpoints require authentication via JWT Bearer token.

#### **Login Endpoint**
```http
POST /api/auth/login
Content-Type: application/json

{
  "email": "admin@hotel.com",
  "password": "admin123"
}
```

**Response:**
```json
{
  "success": true,
  "token": "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9...",
  "user": {
    "id": "1",
    "email": "admin@hotel.com",
    "name": "John Admin",
    "role": "administrator"
  }
}
```

#### **Using Authentication Token**
```http
Authorization: Bearer eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9...
```

### **Demo Accounts**

| Role | Email | Password | Permissions |
|------|-------|----------|-------------|
| **Administrator** | `admin@hotel.com` | `admin123` | Full system access |
| **Staff** | `staff@hotel.com` | `staff123` | Hotel operations |
| **Guest** | `guest@hotel.com` | `guest123` | Personal data only |

---

## 🏨 **Hotels API**

### **Get All Hotels**
```http
GET /api/hotels
Authorization: Bearer <token>
```

**Response:**
```json
{
  "success": true,
  "data": [
    {
      "id": "1",
      "name": "Coastal Grand Hotel - Ooty",
      "location": "Ooty, Tamil Nadu",
      "totalRooms": 25,
      "activeRooms": 21,
      "occupancy": 84,
      "status": "active",
      "manager": {
        "name": "Rajesh Kumar",
        "phone": "+91 90476 28844",
        "email": "rajesh.kumar@coastalgrand.com"
      }
    }
  ]
}
```

### **Get Hotel by ID**
```http
GET /api/hotel/:hotelId
Authorization: Bearer <token>
```

**Parameters:**
- `hotelId` (string): Hotel identifier (1-8)

**Response:**
```json
{
  "success": true,
  "data": {
    "id": "1",
    "name": "Coastal Grand Hotel - Ooty",
    "location": "Ooty, Tamil Nadu",
    "address": "456 Hill Road, Ooty, Tamil Nadu",
    "phone": "+91 90476 28844",
    "email": "rajesh.kumar@coastalgrand.com",
    "rating": 4.7,
    "totalRooms": 25,
    "activeRooms": 21,
    "occupancy": 84,
    "status": "active",
    "lastActivity": "2 minutes ago"
  }
}
```

### **Update Hotel**
```http
PUT /api/hotel/:hotelId
Authorization: Bearer <token>
Content-Type: application/json

{
  "name": "Updated Hotel Name",
  "location": "Updated Location",
  "phone": "+91 90476 28844"
}
```

**Response:**
```json
{
  "success": true,
  "message": "Hotel updated successfully"
}
```

---

## 🏠 **Rooms API**

### **Get Hotel Rooms**
```http
GET /api/rooms/:hotelId
Authorization: Bearer <token>
```

**Parameters:**
- `hotelId` (string): Hotel identifier (1-8)

**Response:**
```json
{
  "success": true,
  "data": [
    {
      "id": 1,
      "hotelId": "1",
      "number": "101",
      "status": "occupied",
      "hasMasterKey": true,
      "hasLowPower": false,
      "powerStatus": "on",
      "occupantType": "guest"
    }
  ]
}
```

**Room Status Values:**
- `occupied`: Room is currently occupied
- `vacant`: Room is available
- `maintenance`: Room under maintenance

**Occupant Types:**
- `guest`: Regular hotel guest
- `manager`: Hotel manager
- `maintenance`: Maintenance staff

---

## 📊 **Activity API**

### **Get Hotel Activity**
```http
GET /api/activity/:hotelId
Authorization: Bearer <token>
```

**Parameters:**
- `hotelId` (string): Hotel identifier (1-8)

**Response:**
```json
{
  "success": true,
  "data": [
    {
      "id": "1",
      "hotelId": "1",
      "type": "checkin",
      "action": "Guest checked in to Room 101",
      "user": "John Smith",
      "time": "2024-12-28T10:30:00Z",
      "room": "101"
    }
  ]
}
```

**Activity Types:**
- `checkin`: Guest check-in event
- `checkout`: Guest check-out event
- `security`: Security alert or incident
- `service`: Service request or completion
- `maintenance`: Maintenance activity
- `system`: System-generated event

---

## 📈 **Analytics API**

### **Get Hotel Analytics**
```http
GET /api/analytics/:hotelId
Authorization: Bearer <token>
```

**Query Parameters:**
- `period` (optional): `day`, `week`, `month`, `year`
- `metric` (optional): `occupancy`, `revenue`, `satisfaction`

**Response:**
```json
{
  "success": true,
  "data": {
    "occupancy": {
      "current": 84,
      "trend": "+5.2%",
      "history": [
        {"date": "2024-12-01", "value": 78},
        {"date": "2024-12-02", "value": 82}
      ]
    },
    "revenue": {
      "current": 72450,
      "trend": "+12.3%",
      "breakdown": {
        "rooms": 52450,
        "services": 12800,
        "spa": 4200,
        "other": 3000
      }
    }
  }
}
```

---

## 🔔 **Attendance API**

### **Get Attendance Records**
```http
GET /api/attendance/:hotelId
Authorization: Bearer <token>
```

**Response:**
```json
{
  "success": true,
  "data": [
    {
      "hotelId": "1",
      "card_uid": "AF4D991F",
      "role": "Guest",
      "check_in": "2024-12-28T10:30:00Z",
      "check_out": "2024-12-28T18:45:00Z",
      "duration": 29700,
      "room": "101"
    }
  ]
}
```

---

## 🚨 **Alerts API**

### **Get Security Alerts**
```http
GET /api/alerts/:hotelId
Authorization: Bearer <token>
```

**Response:**
```json
{
  "success": true,
  "data": [
    {
      "hotelId": "1",
      "card_uid": "UNKNOWN",
      "role": "Security",
      "alert_message": "Unauthorized access attempt detected",
      "triggered_at": "2024-12-28T15:20:00Z",
      "room": "205",
      "severity": "high"
    }
  ]
}
```

**Alert Severity Levels:**
- `low`: Minor security events
- `medium`: Moderate security concerns
- `high`: Critical security alerts
- `critical`: Emergency situations

---

## ❌ **Denied Access API**

### **Get Denied Access Attempts**
```http
GET /api/denied_access/:hotelId
Authorization: Bearer <token>
```

**Response:**
```json
{
  "success": true,
  "data": [
    {
      "hotelId": "1",
      "card_uid": "INVALID123",
      "role": "Unknown",
      "denial_reason": "Unauthorized card",
      "attempted_at": "2024-12-28T14:15:00Z",
      "room": "301"
    }
  ]
}
```

---

## 👥 **Users API**

### **Get Hotel Users**
```http
GET /api/users/:hotelId
Authorization: Bearer <token>
```

**Response:**
```json
{
  "success": true,
  "data": [
    {
      "id": "1",
      "hotelId": "1",
      "name": "John Smith",
      "email": "john.smith@hotel.com",
      "role": "manager",
      "status": "active",
      "lastLogin": "2 hours ago"
    }
  ]
}
```

---

## 💳 **Cards API**

### **Get Hotel Key Cards**
```http
GET /api/cards/:hotelId
Authorization: Bearer <token>
```

**Response:**
```json
{
  "success": true,
  "data": [
    {
      "id": "CARD001",
      "hotelId": "1",
      "roomNumber": "101",
      "guestName": "Alice Johnson",
      "status": "active",
      "expiryDate": "2024-12-31",
      "lastUsed": "2 hours ago"
    }
  ]
}
```

---

## 🔍 **Health Check API**

### **System Health**
```http
GET /health
```

**Response:**
```json
{
  "status": "OK",
  "timestamp": "2024-12-28T15:41:19.315Z",
  "uptime": 86400,
  "version": "1.0.0"
}
```

### **Environment Health**
```http
GET /api/health/env
Authorization: Bearer <token>
```

**Response:**
```json
{
  "timestamp": "2024-12-28T15:41:19.315Z",
  "environment": "production",
  "database": "connected",
  "jwt": "configured",
  "cors": "configured",
  "frontend": "configured",
  "port": 3000
}
```

---

## 🔄 **Real-time Communication**

### **WebSocket Connection**

#### **Connection URL**
```javascript
const ws = new WebSocket('wss://coastal-grand-back.onrender.com/ws');
```

#### **Connection Events**
```javascript
ws.onopen = () => {
  console.log('WebSocket connected');
};

ws.onmessage = (event) => {
  const data = JSON.parse(event.data);
  console.log('Received:', data);
};

ws.onclose = (event) => {
  console.log('WebSocket disconnected:', event.code);
};
```

#### **Message Format**
```json
{
  "event": "roomUpdate:1",
  "data": {
    "roomNum": "101",
    "status": "occupied",
    "occupantType": "guest",
    "powerStatus": "on"
  }
}
```

### **Server-Sent Events (SSE)**

#### **Connection URL**
```javascript
const eventSource = new EventSource('/api/events/1');
```

#### **Event Handling**
```javascript
eventSource.onmessage = (event) => {
  const data = JSON.parse(event.data);
  console.log('SSE Event:', data);
};

eventSource.onerror = (error) => {
  console.error('SSE Error:', error);
};
```

---

## 📡 **MQTT Topics**

### **Topic Structure**
```
campus/room/{building}/{floor}/{roomNum}/{type}
```

### **Topic Examples**
- `campus/room/main/1/101/attendance`
- `campus/room/main/1/101/alerts`
- `campus/room/main/1/101/denied_access`

### **Message Types**

#### **Attendance Messages**
```json
{
  "card_uid": "AF4D991F",
  "role": "Guest",
  "check_in": "2024-12-28T10:30:00Z",
  "room": "101"
}
```

#### **Alert Messages**
```json
{
  "card_uid": "UNKNOWN",
  "role": "Security",
  "alert_message": "Unauthorized access attempt",
  "triggered_at": "2024-12-28T15:20:00Z",
  "room": "205"
}
```

#### **Denied Access Messages**
```json
{
  "card_uid": "INVALID123",
  "role": "Unknown",
  "denial_reason": "Unauthorized card",
  "attempted_at": "2024-12-28T14:15:00Z",
  "room": "301"
}
```

---

## 🔧 **ESP32 Integration**

### **HTTP Endpoint for ESP32**
```http
POST /api/mqtt-data
Content-Type: application/json

{
  "topic": "campus/room/main/1/101/attendance",
  "data": {
    "card_uid": "AF4D991F",
    "role": "Guest",
    "check_in": "2024-12-28T10:30:00Z"
  }
}
```

### **MQTT Simulation Endpoint**
```http
POST /api/simulate-mqtt
Content-Type: application/json

{
  "topic": "campus/room/main/1/101/attendance",
  "payload": {
    "card_uid": "AF4D991F",
    "role": "Guest",
    "check_in": "2024-12-28T10:30:00Z"
  }
}
```

---

## ❌ **Error Handling**

### **Error Response Format**
```json
{
  "success": false,
  "error": "Error message",
  "code": "ERROR_CODE",
  "timestamp": "2024-12-28T15:41:19.315Z"
}
```

### **HTTP Status Codes**

| Code | Description | Usage |
|------|-------------|-------|
| **200** | OK | Successful request |
| **201** | Created | Resource created successfully |
| **400** | Bad Request | Invalid request parameters |
| **401** | Unauthorized | Authentication required |
| **403** | Forbidden | Insufficient permissions |
| **404** | Not Found | Resource not found |
| **429** | Too Many Requests | Rate limit exceeded |
| **500** | Internal Server Error | Server error |
| **503** | Service Unavailable | Service temporarily unavailable |

### **Common Error Codes**

| Code | Description |
|------|-------------|
| `INVALID_TOKEN` | JWT token is invalid or expired |
| `INSUFFICIENT_PERMISSIONS` | User lacks required permissions |
| `HOTEL_NOT_FOUND` | Specified hotel does not exist |
| `ROOM_NOT_FOUND` | Specified room does not exist |
| `VALIDATION_ERROR` | Request validation failed |
| `DATABASE_ERROR` | Database operation failed |
| `RATE_LIMIT_EXCEEDED` | Too many requests |

---

## 🔒 **Security**

### **Rate Limiting**
- **Window**: 15 minutes
- **Max Requests**: 100 per window
- **Headers**: `X-RateLimit-Limit`, `X-RateLimit-Remaining`

### **CORS Policy**
```javascript
{
  "origin": [
    "https://coastal-grand-tolr.vercel.app",
    "http://localhost:3000"
  ],
  "credentials": true,
  "methods": ["GET", "POST", "PUT", "DELETE", "OPTIONS"]
}
```

### **Security Headers**
- `X-Content-Type-Options: nosniff`
- `X-Frame-Options: DENY`
- `X-XSS-Protection: 1; mode=block`
- `Strict-Transport-Security: max-age=31536000`

---

## 📊 **API Usage Examples**

### **JavaScript/TypeScript**
```typescript
/**
 * @brief API service class for hotel management
 */
class HotelAPI {
  private baseURL = 'https://coastal-grand-back.onrender.com';
  private token: string;

  constructor(token: string) {
    this.token = token;
  }

  /**
   * @brief Get all hotels
   * @returns Promise<Hotel[]>
   */
  async getHotels(): Promise<Hotel[]> {
    const response = await fetch(`${this.baseURL}/api/hotels`, {
      headers: {
        'Authorization': `Bearer ${this.token}`,
        'Content-Type': 'application/json'
      }
    });
    
    if (!response.ok) {
      throw new Error(`HTTP error! status: ${response.status}`);
    }
    
    const result = await response.json();
    return result.data;
  }

  /**
   * @brief Get hotel by ID
   * @param hotelId Hotel identifier
   * @returns Promise<Hotel>
   */
  async getHotel(hotelId: string): Promise<Hotel> {
    const response = await fetch(`${this.baseURL}/api/hotel/${hotelId}`, {
      headers: {
        'Authorization': `Bearer ${this.token}`,
        'Content-Type': 'application/json'
      }
    });
    
    const result = await response.json();
    return result.data;
  }
}
```

### **Python**
```python
import requests
import json

class HotelAPI:
    """API client for RFID Hotel Management System"""
    
    def __init__(self, token: str):
        self.base_url = "https://coastal-grand-back.onrender.com"
        self.headers = {
            "Authorization": f"Bearer {token}",
            "Content-Type": "application/json"
        }
    
    def get_hotels(self):
        """Get all hotels"""
        response = requests.get(f"{self.base_url}/api/hotels", headers=self.headers)
        response.raise_for_status()
        return response.json()["data"]
    
    def get_hotel(self, hotel_id: str):
        """Get hotel by ID"""
        response = requests.get(f"{self.base_url}/api/hotel/{hotel_id}", headers=self.headers)
        response.raise_for_status()
        return response.json()["data"]
```

### **cURL Examples**
```bash
# Get all hotels
curl -X GET "https://coastal-grand-back.onrender.com/api/hotels" \
  -H "Authorization: Bearer YOUR_TOKEN" \
  -H "Content-Type: application/json"

# Get specific hotel
curl -X GET "https://coastal-grand-back.onrender.com/api/hotel/1" \
  -H "Authorization: Bearer YOUR_TOKEN" \
  -H "Content-Type: application/json"

# Update hotel
curl -X PUT "https://coastal-grand-back.onrender.com/api/hotel/1" \
  -H "Authorization: Bearer YOUR_TOKEN" \
  -H "Content-Type: application/json" \
  -d '{"name": "Updated Hotel Name"}'
```

---

## 📈 **Performance**

### **Response Times**
- **Average**: < 200ms
- **95th percentile**: < 500ms
- **99th percentile**: < 1000ms

### **Throughput**
- **Max requests/second**: 1000
- **Concurrent connections**: 100
- **WebSocket connections**: 1000

### **Caching**
- **Static assets**: CDN cached
- **API responses**: 5-minute cache
- **Database queries**: Connection pooling

---

## 🔧 **Development Tools**

### **API Testing**
```bash
# Install dependencies
npm install

# Start development server
npm run dev:backend

# Run API tests
npm run test:api

# Check API health
curl http://localhost:3000/health
```

### **Postman Collection**
Import the API collection for testing:
```json
{
  "info": {
    "name": "RFID Hotel Management API",
    "schema": "https://schema.getpostman.com/json/collection/v2.1.0/collection.json"
  },
  "auth": {
    "type": "bearer",
    "bearer": [
      {
        "key": "token",
        "value": "{{jwt_token}}",
        "type": "string"
      }
    ]
  }
}
```

---

## 📞 **Support**

### **API Support**
- **Documentation**: This comprehensive API guide
- **Issues**: GitHub Issues for bug reports
- **Questions**: GitHub Discussions for API questions
- **Response Time**: 24-48 hours

### **Rate Limits**
If you need higher rate limits for production use, please contact the development team.

---

**Last Updated**: December 2024  
**API Version**: 1.0.0  
**Status**: Production Ready ✅