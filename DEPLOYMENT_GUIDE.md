/**
 * @file DEPLOYMENT_GUIDE.md
 * @brief Comprehensive Deployment Guide for RFID Hotel Management System
 * @author Development Team
 * @date 2024
 * @version 1.0.0
 * 
 * @mainpage RFID Hotel Management System - Complete Deployment Guide
 * 
 * @section intro_sec Introduction
 * 
 * This document provides complete deployment procedures for the RFID Hotel Management System,
 * including frontend (Next.js), backend (Node.js/Express), database (MongoDB), and ESP32 hardware integration.
 * 
 * @section arch_sec System Architecture
 * 
 * The system consists of:
 * - **Frontend**: Next.js 15 with TypeScript (Deployed on Vercel)
 * - **Backend**: Node.js/Express with MQTT broker (Deployed on Render)
 * - **Database**: MongoDB Atlas (Cloud)
 * - **Hardware**: ESP32 with RFID readers (On-premise)
 * - **Real-time**: WebSocket + MQTT + Server-Sent Events
 * 
 * @section requirements_sec System Requirements
 * 
 * ### Software Requirements
 * - Node.js 18+ (LTS recommended)
 * - npm/yarn/pnpm package manager
 * - Git version control
 * - MongoDB Atlas account
 * - Vercel account (for frontend)
 * - Render account (for backend)
 * 
 * ### Hardware Requirements
 * - ESP32 development board
 * - MFRC522 RFID reader module
 * - RFID cards/tags
 * - Jumper wires and breadboard
 * - Stable WiFi connection
 */

# 🏨 RFID Hotel Management System - Complete Deployment Guide

## 📋 Table of Contents

1. [Environment Configuration](#environment-configuration)
2. [Frontend Deployment (Vercel)](#frontend-deployment)
3. [Backend Deployment (Render)](#backend-deployment)
4. [Database Setup (MongoDB Atlas)](#database-setup)
5. [ESP32 Hardware Setup](#esp32-hardware-setup)
6. [Testing & Verification](#testing-verification)
7. [Troubleshooting](#troubleshooting)
8. [Maintenance](#maintenance)

---

## 🔧 Environment Configuration

### ⚠️ **CRITICAL: Environment Variables Analysis**

**Current Status Check:**

#### Frontend Environment (`.env`)
```properties
NEXT_PUBLIC_API_URL=https://coastal-grand-back.onrender.com
NEXT_PUBLIC_SOCKET_URL=https://coastal-grand-back.onrender.com
```

#### Backend Environment (`Backend/.env`)
```properties
MONGO_URL=mongodb+srv://yahyaimthiyas:23csr243@cluster0.hsasoax.mongodb.net/hotel_db?retryWrites=true&w=majority
PORT=3000
MQTT_PORT=1883
FRONTEND_URL=https://coastal-grand-tolr.vercel.app
```

### 🚨 **MISSING ENVIRONMENT VARIABLES**

**Required additions for production:**

#### Frontend (`.env.local`)
```properties
# API Configuration
NEXT_PUBLIC_API_URL=https://coastal-grand-back.onrender.com
NEXT_PUBLIC_SOCKET_URL=https://coastal-grand-back.onrender.com

# Authentication (Add these)
NEXTAUTH_SECRET=your-super-secret-jwt-key-here
NEXTAUTH_URL=https://coastal-grand-tolr.vercel.app

# Analytics (Optional)
NEXT_PUBLIC_GA_ID=your-google-analytics-id
NEXT_PUBLIC_HOTJAR_ID=your-hotjar-id

# Feature Flags
NEXT_PUBLIC_ENABLE_ANALYTICS=true
NEXT_PUBLIC_ENABLE_REAL_TIME=true
```

#### Backend (`.env`)
```properties
# Database
MONGO_URL=mongodb+srv://yahyaimthiyas:23csr243@cluster0.hsasoax.mongodb.net/hotel_db?retryWrites=true&w=majority

# Server Configuration
PORT=3000
NODE_ENV=production
MQTT_PORT=1883

# Frontend URLs
FRONTEND_URL=https://coastal-grand-tolr.vercel.app
CORS_ORIGINS=https://coastal-grand-tolr.vercel.app,http://localhost:3000

# Security (Add these)
JWT_SECRET=your-jwt-secret-key-here
SESSION_SECRET=your-session-secret-here
ENCRYPTION_KEY=your-32-character-encryption-key

# External Services (Add these)
SMTP_HOST=smtp.gmail.com
SMTP_PORT=587
SMTP_USER=your-email@gmail.com
SMTP_PASS=your-app-password

# Monitoring (Optional)
SENTRY_DSN=your-sentry-dsn
LOG_LEVEL=info

# Rate Limiting
RATE_LIMIT_WINDOW=15
RATE_LIMIT_MAX=100
```

---

## 🚀 Frontend Deployment (Vercel)

### **Step 1: Prepare Repository**

```bash
# Clone the repository
git clone https://github.com/your-username/rfid-hotel-management.git
cd rfid-hotel-management

# Install dependencies
npm install
# or
pnpm install
```

### **Step 2: Configure Environment Variables**

Create `.env.local`:
```properties
NEXT_PUBLIC_API_URL=https://coastal-grand-back.onrender.com
NEXT_PUBLIC_SOCKET_URL=https://coastal-grand-back.onrender.com
NEXTAUTH_SECRET=generate-a-secure-secret-key
NEXTAUTH_URL=https://your-app-name.vercel.app
```

### **Step 3: Deploy to Vercel**

#### Option A: Vercel CLI
```bash
# Install Vercel CLI
npm i -g vercel

# Login to Vercel
vercel login

# Deploy
vercel --prod
```

#### Option B: GitHub Integration
1. Push code to GitHub
2. Connect repository to Vercel
3. Configure environment variables in Vercel dashboard
4. Deploy automatically

### **Step 4: Vercel Configuration**

Create `vercel.json`:
```json
{
  "version": 2,
  "builds": [
    {
      "src": "package.json",
      "use": "@vercel/next"
    }
  ],
  "routes": [
    {
      "src": "/(.*)",
      "dest": "/"
    }
  ],
  "env": {
    "NEXT_PUBLIC_API_URL": "https://coastal-grand-back.onrender.com",
    "NEXT_PUBLIC_SOCKET_URL": "https://coastal-grand-back.onrender.com"
  }
}
```

---

## 🖥️ Backend Deployment (Render)

### **Step 1: Prepare Backend**

```bash
cd Backend

# Install dependencies
npm install

# Test locally
npm start
```

### **Step 2: Create Render Service**

1. **Connect Repository**: Link your GitHub repository
2. **Service Configuration**:
   - **Name**: `coastal-grand-back`
   - **Environment**: `Node`
   - **Build Command**: `npm install`
   - **Start Command**: `node index.js`
   - **Instance Type**: `Starter` (Free tier)

### **Step 3: Environment Variables in Render**

Add these in Render dashboard:
```properties
MONGO_URL=mongodb+srv://yahyaimthiyas:23csr243@cluster0.hsasoax.mongodb.net/hotel_db?retryWrites=true&w=majority
PORT=3000
NODE_ENV=production
FRONTEND_URL=https://coastal-grand-tolr.vercel.app
CORS_ORIGINS=https://coastal-grand-tolr.vercel.app,http://localhost:3000
JWT_SECRET=your-jwt-secret-here
SESSION_SECRET=your-session-secret-here
```

### **Step 4: Render Configuration**

Create `render.yaml`:
```yaml
services:
  - type: web
    name: coastal-grand-back
    env: node
    plan: starter
    buildCommand: npm install
    startCommand: node index.js
    envVars:
      - key: NODE_ENV
        value: production
      - key: PORT
        value: 3000
```

---

## 🗄️ Database Setup (MongoDB Atlas)

### **Step 1: Create MongoDB Atlas Cluster**

1. **Sign up**: Create MongoDB Atlas account
2. **Create Cluster**: Choose free tier (M0)
3. **Configure Security**:
   - Create database user
   - Add IP whitelist (0.0.0.0/0 for development)

### **Step 2: Database Configuration**

```javascript
/**
 * @brief MongoDB connection configuration
 * @param mongoUrl Connection string from Atlas
 * @return Promise<Connection> Database connection
 */
const connectDB = async (mongoUrl) => {
  try {
    await mongoose.connect(mongoUrl, {
      useNewUrlParser: true,
      useUnifiedTopology: true,
      maxPoolSize: 10,
      serverSelectionTimeoutMS: 5000,
      socketTimeoutMS: 45000,
    });
    console.log('MongoDB Atlas connected successfully');
  } catch (error) {
    console.error('MongoDB connection error:', error);
    process.exit(1);
  }
};
```

### **Step 3: Database Schemas**

The system uses these collections:
- `hotels` - Hotel information
- `rooms` - Room status and details
- `attendance` - Check-in/out records
- `alerts` - Security alerts
- `denied` - Access denied logs
- `users` - System users
- `cards` - RFID card management
- `activities` - Activity logs

---

## 🔌 ESP32 Hardware Setup

### **Step 1: Hardware Connections**

```cpp
/**
 * @brief ESP32 Pin Configuration
 * @details MFRC522 RFID Reader connections
 */
#define RST_PIN 22    ///< Reset pin for MFRC522
#define SS_PIN 21     ///< Slave Select pin for MFRC522

// SPI Connections:
// MFRC522    ESP32
// --------   -----
// RST        GPIO 22
// SDA(SS)    GPIO 21
// MOSI       GPIO 23
// MISO       GPIO 19
// SCK        GPIO 18
// 3.3V       3.3V
// GND        GND
```

### **Step 2: WiFi Configuration**

```cpp
/**
 * @brief WiFi credentials configuration
 * @warning Update these values for your network
 */
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";
```

### **Step 3: Server Configuration**

```cpp
/**
 * @brief WebSocket server configuration
 * @param websocketHost Backend server hostname
 * @param websocketPort HTTPS port (443 for SSL)
 * @param websocketPath MQTT WebSocket endpoint
 */
const char* websocketHost = "coastal-grand-back.onrender.com";
const int   websocketPort = 443;
const char* websocketPath = "/mqtt";
```

### **Step 4: Room Configuration**

```cpp
/**
 * @brief Room identification parameters
 * @param roomNumber Physical room number
 * @param building Building identifier
 * @param floorNumber Floor/Hotel ID (maps to backend hotelId)
 */
const char* roomNumber  = "202";        // Change per room
const char* building    = "main";       // Building identifier
const char* floorNumber = "3";          // Hotel ID (1-8)
```

### **Step 5: RFID Card Configuration**

```cpp
/**
 * @brief User authentication database
 * @details Maps RFID UIDs to user roles
 */
struct UserAuth {
  byte uid[4];          ///< 4-byte RFID UID
  const char* role;     ///< User role (Guest/Staff/Manager/Maintenance)
};

UserAuth users[] = {
  {{0xAF, 0x4D, 0x99, 0x1F}, "Maintenance"},
  {{0xBF, 0xD1, 0x07, 0x1F}, "Manager"},
  {{0xB2, 0xF9, 0x7C, 0x00}, "Guest"}
  // Add more cards as needed
};
```

### **Step 6: Upload ESP32 Code**

```bash
# Install Arduino IDE or PlatformIO
# Install required libraries:
# - MFRC522
# - WebSocketsClient
# - ArduinoJson
# - WiFi (built-in)

# Upload code to ESP32
# Monitor serial output for debugging
```

---

## 🧪 Testing & Verification

### **Step 1: Backend API Testing**

```bash
# Test backend endpoints
curl https://coastal-grand-back.onrender.com/health
curl https://coastal-grand-back.onrender.com/api/hotels
```

### **Step 2: Frontend Testing**

```bash
# Test frontend
curl https://coastal-grand-tolr.vercel.app
```

### **Step 3: WebSocket Testing**

```javascript
/**
 * @brief WebSocket connection test
 * @param url WebSocket server URL
 */
const testWebSocket = () => {
  const ws = new WebSocket('wss://coastal-grand-back.onrender.com/ws');
  
  ws.onopen = () => console.log('WebSocket connected');
  ws.onmessage = (event) => console.log('Received:', event.data);
  ws.onerror = (error) => console.error('WebSocket error:', error);
};
```

### **Step 4: ESP32 Testing**

1. **Serial Monitor**: Check connection status
2. **RFID Test**: Scan test cards
3. **Data Flow**: Verify data reaches backend
4. **Real-time Updates**: Check frontend updates

---

## 🔧 Troubleshooting

### **Common Issues & Solutions**

#### **1. Environment Variables Not Loading**
```bash
# Check .env files exist and are properly formatted
ls -la .env*
cat .env

# Restart services after env changes
```

#### **2. CORS Errors**
```javascript
// Backend: Update CORS configuration
app.use(cors({
  origin: [
    'https://coastal-grand-tolr.vercel.app',
    'http://localhost:3000'
  ],
  credentials: true
}));
```

#### **3. WebSocket Connection Failed**
```javascript
// Check WebSocket URL and SSL configuration
const wsUrl = 'wss://coastal-grand-back.onrender.com/ws';
```

#### **4. ESP32 Connection Issues**
```cpp
// Check WiFi credentials and server URL
const char* ssid = "YOUR_ACTUAL_WIFI_NAME";
const char* password = "YOUR_ACTUAL_PASSWORD";
```

#### **5. Database Connection Failed**
```bash
# Verify MongoDB Atlas IP whitelist
# Check connection string format
# Ensure user has proper permissions
```

---

## 🔄 Maintenance

### **Regular Tasks**

#### **Daily**
- Monitor system logs
- Check ESP32 connectivity
- Verify real-time updates

#### **Weekly**
- Database backup
- Performance monitoring
- Security audit

#### **Monthly**
- Update dependencies
- Review access logs
- System optimization

### **Monitoring Commands**

```bash
# Check backend logs (Render)
render logs --service coastal-grand-back

# Check frontend logs (Vercel)
vercel logs

# Monitor database (MongoDB Atlas)
# Use Atlas dashboard for monitoring
```

---

## 📊 Performance Optimization

### **Frontend Optimization**

```javascript
/**
 * @brief Next.js performance configuration
 */
const nextConfig = {
  experimental: {
    optimizeCss: true,
    optimizeImages: true,
  },
  images: {
    domains: ['coastal-grand-back.onrender.com'],
    formats: ['image/webp', 'image/avif'],
  },
  compress: true,
  poweredByHeader: false,
};
```

### **Backend Optimization**

```javascript
/**
 * @brief Express.js performance middleware
 */
app.use(compression());
app.use(helmet());
app.use(express.json({ limit: '10mb' }));
app.use(express.urlencoded({ extended: true, limit: '10mb' }));
```

---

## 🔐 Security Considerations

### **Environment Security**
- Use strong, unique secrets
- Rotate keys regularly
- Never commit secrets to git
- Use environment-specific configurations

### **API Security**
- Implement rate limiting
- Use HTTPS everywhere
- Validate all inputs
- Implement proper authentication

### **Database Security**
- Use connection encryption
- Implement proper indexing
- Regular security updates
- Monitor access patterns

---

## 📞 Support & Contact

For deployment issues or questions:
- **Documentation**: This guide
- **Repository**: GitHub repository
- **Issues**: GitHub Issues section
- **Email**: development-team@company.com

---

**Last Updated**: December 2024  
**Version**: 1.0.0  
**Status**: Production Ready ✅