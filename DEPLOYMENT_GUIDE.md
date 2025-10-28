/**
 * @file DEPLOYMENT_GUIDE.md
 * @brief Complete Deployment Guide for RFID Hotel Management System
 * @author Development Team
 * @version 1.0.0
 * @date December 2024
 * 
 * @section deployment_overview Deployment Overview
 * 
 * This comprehensive guide covers all deployment procedures for the RFID Hotel
 * Management System, including frontend, backend, database, and hardware components.
 * All procedures are documented with complete parameters and step-by-step instructions.
 * 
 * @section deployment_architecture Deployment Architecture
 * - Frontend: Vercel (Next.js 15 + TypeScript)
 * - Backend: Render.com (Node.js + Express)
 * - Database: MongoDB Atlas (Cloud)
 * - Hardware: ESP32 with MFRC522 RFID readers
 * - Real-time: WebSocket + MQTT + Server-Sent Events
 */

# 🚀 Complete Deployment Guide

## 📋 **Table of Contents**

- [🎯 Deployment Overview](#deployment-overview)
- [🔧 Prerequisites](#prerequisites)
- [🌐 Frontend Deployment (Vercel)](#frontend-deployment-vercel)
- [⚙️ Backend Deployment (Render)](#backend-deployment-render)
- [🗄️ Database Setup (MongoDB Atlas)](#database-setup-mongodb-atlas)
- [🔌 Hardware Deployment (ESP32)](#hardware-deployment-esp32)
- [🔄 CI/CD Pipeline](#cicd-pipeline)
- [✅ Verification & Testing](#verification--testing)
- [🔧 Troubleshooting](#troubleshooting)

---

## 🎯 **Deployment Overview**

### **System Architecture**

```
┌─────────────────┐    ┌─────────────────┐    ┌─────────────────┐
│   Frontend      │    │    Backend      │    │    Database     │
│   (Vercel)      │◄──►│   (Render)      │◄──►│ (MongoDB Atlas) │
│   Next.js 15    │    │   Node.js       │    │   Cloud DB      │
└─────────────────┘    └─────────────────┘    └─────────────────┘
         ▲                       ▲                       ▲
         │                       │                       │
         ▼                       ▼                       ▼
┌─────────────────┐    ┌─────────────────┐    ┌─────────────────┐
│   ESP32 RFID    │    │   MQTT Broker   │    │   WebSocket     │
│   Hardware      │◄──►│   (Aedes)       │◄──►│   Real-time     │
│   MFRC522       │    │   Pub/Sub       │    │   Updates       │
└─────────────────┘    └─────────────────┘    └─────────────────┘
```

### **Deployment Status**

| Component | Platform | Status | URL |
|-----------|----------|--------|-----|
| **Frontend** | Vercel | ✅ Live | https://coastal-grand-tolr.vercel.app |
| **Backend** | Render | ✅ Live | https://coastal-grand-back.onrender.com |
| **Database** | MongoDB Atlas | ✅ Active | Cloud Cluster |
| **Hardware** | ESP32 | 🔧 Ready | Local Network |

---

## 🔧 **Prerequisites**

### **Required Accounts**
- ✅ **Vercel Account** (Frontend deployment)
- ✅ **Render Account** (Backend deployment)
- ✅ **MongoDB Atlas Account** (Database hosting)
- ✅ **GitHub Account** (Code repository)

### **Required Tools**
```bash
# Node.js and npm
node --version  # v18.0.0 or higher
npm --version   # v8.0.0 or higher

# Vercel CLI
npm install -g vercel

# Git
git --version

# Arduino IDE (for ESP32)
# Download from: https://www.arduino.cc/en/software
```

### **Environment Files Required**
- `.env.local` (Frontend)
- `Backend/.env` (Backend)
- `ESP32 code/config.h` (Hardware)

---

## 🌐 **Frontend Deployment (Vercel)**

### **Step 1: Prepare Frontend**

#### **1.1 Environment Configuration**
Create `.env.local` with all required variables:

```properties
# API Configuration
NEXT_PUBLIC_API_URL=https://coastal-grand-back.onrender.com
NEXT_PUBLIC_SOCKET_URL=https://coastal-grand-back.onrender.com

# Authentication
NEXTAUTH_SECRET=your-super-secret-jwt-key-minimum-32-characters
NEXTAUTH_URL=https://coastal-grand-tolr.vercel.app

# Feature Flags
NEXT_PUBLIC_ENABLE_ANALYTICS=true
NEXT_PUBLIC_ENABLE_REAL_TIME=true
NEXT_PUBLIC_ENABLE_NOTIFICATIONS=true

# Security
NEXT_PUBLIC_CORS_ORIGIN=https://coastal-grand-tolr.vercel.app
```

#### **1.2 Build Configuration**
Verify `next.config.mjs`:

```javascript
/** @type {import('next').NextConfig} */
const nextConfig = {
  experimental: {
    appDir: true,
  },
  env: {
    NEXT_PUBLIC_API_URL: process.env.NEXT_PUBLIC_API_URL,
    NEXT_PUBLIC_SOCKET_URL: process.env.NEXT_PUBLIC_SOCKET_URL,
  },
  async headers() {
    return [
      {
        source: '/api/:path*',
        headers: [
          { key: 'Access-Control-Allow-Origin', value: '*' },
          { key: 'Access-Control-Allow-Methods', value: 'GET,POST,PUT,DELETE,OPTIONS' },
          { key: 'Access-Control-Allow-Headers', value: 'Content-Type,Authorization' },
        ],
      },
    ];
  },
};

export default nextConfig;
```

### **Step 2: Deploy to Vercel**

#### **2.1 Manual Deployment**
```bash
# Install Vercel CLI
npm install -g vercel

# Login to Vercel
vercel login

# Deploy to production
vercel --prod

# Follow prompts:
# ? Set up and deploy "~/coastal_grand-main"? [Y/n] Y
# ? Which scope do you want to deploy to? [Your Account]
# ? Link to existing project? [y/N] N
# ? What's your project's name? rfid-hotel-management
# ? In which directory is your code located? ./
```

#### **2.2 Automated Deployment via GitHub**

1. **Connect Repository**:
   - Go to [Vercel Dashboard](https://vercel.com/dashboard)
   - Click "New Project"
   - Import from GitHub: `rfid-hotel-management-system`

2. **Configure Build Settings**:
   ```
   Framework Preset: Next.js
   Root Directory: ./
   Build Command: npm run build
   Output Directory: .next
   Install Command: npm install
   ```

3. **Environment Variables**:
   Add all variables from `.env.local` in Vercel dashboard

4. **Deploy**:
   - Click "Deploy"
   - Wait for build completion
   - Verify deployment at generated URL

### **Step 3: Custom Domain (Optional)**
```bash
# Add custom domain
vercel domains add yourdomain.com

# Configure DNS
# Add CNAME record: www -> cname.vercel-dns.com
# Add A record: @ -> 76.76.19.61
```

---

## ⚙️ **Backend Deployment (Render)**

### **Step 1: Prepare Backend**

#### **1.1 Environment Configuration**
Create `Backend/.env`:

```properties
# Server Configuration
PORT=3000
NODE_ENV=production

# Database
MONGODB_URI=mongodb+srv://username:password@cluster.mongodb.net/hotel_management

# Authentication
JWT_SECRET=your-super-secret-jwt-key-for-backend-minimum-32-chars
JWT_EXPIRES_IN=7d

# CORS
CORS_ORIGIN=https://coastal-grand-tolr.vercel.app

# MQTT Configuration
MQTT_BROKER_URL=mqtt://localhost:1883
MQTT_USERNAME=hotel_system
MQTT_PASSWORD=secure_mqtt_password

# Email Configuration (Optional)
SMTP_HOST=smtp.gmail.com
SMTP_PORT=587
SMTP_USER=your-email@gmail.com
SMTP_PASS=your-app-password

# Rate Limiting
RATE_LIMIT_WINDOW_MS=900000
RATE_LIMIT_MAX_REQUESTS=100

# Session Configuration
SESSION_SECRET=your-session-secret-key-minimum-32-characters
```

#### **1.2 Package.json Scripts**
Verify `Backend/package.json`:

```json
{
  "name": "rfid-hotel-backend",
  "version": "1.0.0",
  "scripts": {
    "start": "node index.js",
    "dev": "nodemon index.js",
    "build": "echo 'No build step required'",
    "test": "jest"
  },
  "engines": {
    "node": ">=18.0.0",
    "npm": ">=8.0.0"
  }
}
```

### **Step 2: Deploy to Render**

#### **2.1 Manual Deployment**

1. **Create Render Account**: [render.com](https://render.com)

2. **Create New Web Service**:
   - Connect GitHub repository
   - Select `rfid-hotel-management-system`
   - Configure settings:

```yaml
Name: coastal-grand-back
Environment: Node
Region: Oregon (US West)
Branch: main
Root Directory: Backend
Build Command: npm install
Start Command: node index.js
```

3. **Environment Variables**:
   Add all variables from `Backend/.env`

4. **Advanced Settings**:
```yaml
Auto-Deploy: Yes
Health Check Path: /health
```

#### **2.2 Deployment Configuration**

Create `render.yaml` in project root:

```yaml
services:
  - type: web
    name: coastal-grand-back
    env: node
    region: oregon
    plan: free
    buildCommand: cd Backend && npm install
    startCommand: cd Backend && node index.js
    envVars:
      - key: NODE_ENV
        value: production
      - key: PORT
        value: 10000
      - key: MONGODB_URI
        fromDatabase:
          name: hotel-management-db
          property: connectionString
```

### **Step 3: Health Check Endpoint**

Ensure `Backend/index.js` includes:

```javascript
// Health check endpoint
app.get('/health', (req, res) => {
  res.status(200).json({
    status: 'OK',
    timestamp: new Date().toISOString(),
    uptime: process.uptime(),
    environment: process.env.NODE_ENV,
    version: '1.0.0'
  });
});
```

---

## 🗄️ **Database Setup (MongoDB Atlas)**

### **Step 1: Create MongoDB Atlas Cluster**

#### **1.1 Account Setup**
1. Create account at [MongoDB Atlas](https://cloud.mongodb.com)
2. Create new project: "RFID Hotel Management"
3. Create cluster: "hotel-management-cluster"

#### **1.2 Cluster Configuration**
```yaml
Cluster Tier: M0 Sandbox (Free)
Cloud Provider: AWS
Region: us-east-1
Cluster Name: hotel-management-cluster
MongoDB Version: 6.0
```

### **Step 2: Database Security**

#### **2.1 Network Access**
```
IP Access List:
- 0.0.0.0/0 (Allow access from anywhere)
- Or specific IPs for production
```

#### **2.2 Database Users**
```yaml
Username: hotel_admin
Password: [Generate secure password]
Roles: 
  - Database User
  - Read and write to any database
```

### **Step 3: Connection String**

#### **3.1 Get Connection String**
```
mongodb+srv://hotel_admin:<password>@hotel-management-cluster.xxxxx.mongodb.net/hotel_management?retryWrites=true&w=majority
```

#### **3.2 Database Collections**
The system will auto-create these collections:
- `users` - User accounts and authentication
- `hotels` - Hotel information and settings
- `rooms` - Room details and status
- `bookings` - Reservation data
- `key_cards` - RFID card assignments
- `access_logs` - Entry/exit logs
- `analytics` - Performance metrics

---

## 🔌 **Hardware Deployment (ESP32)**

### **Step 1: Hardware Requirements**

#### **1.1 Components List**
```
✅ ESP32 Development Board (ESP32-WROOM-32)
✅ MFRC522 RFID Reader Module
✅ RFID Cards/Tags (13.56MHz)
✅ Breadboard and Jumper Wires
✅ 3.3V Power Supply
✅ LED Indicators (Optional)
✅ Buzzer (Optional)
```

#### **1.2 Wiring Diagram**
```
ESP32 Pin    MFRC522 Pin    Function
---------    -----------    --------
3.3V         3.3V           Power
GND          GND            Ground
GPIO21       SDA            Serial Data
GPIO18       SCK            Serial Clock
GPIO23       MOSI           Master Out Slave In
GPIO19       MISO           Master In Slave Out
GPIO22       RST            Reset
```

### **Step 2: Software Configuration**

#### **2.1 Arduino IDE Setup**
```cpp
// Install ESP32 Board Package
// File > Preferences > Additional Board Manager URLs:
// https://dl.espressif.com/dl/package_esp32_index.json

// Install Libraries:
// - MFRC522 by GithubCommunity
// - WiFi by Arduino
// - ArduinoJson by Benoit Blanchon
// - PubSubClient by Nick O'Leary
```

#### **2.2 Configuration File**
Update `ESP32 code/config.h`:

```cpp
/**
 * @file config.h
 * @brief ESP32 RFID System Configuration
 */

#ifndef CONFIG_H
#define CONFIG_H

// WiFi Configuration
#define WIFI_SSID "Your_WiFi_Network"
#define WIFI_PASSWORD "Your_WiFi_Password"

// Server Configuration
#define SERVER_URL "https://coastal-grand-back.onrender.com"
#define WEBSOCKET_URL "wss://coastal-grand-back.onrender.com"

// MQTT Configuration
#define MQTT_BROKER "coastal-grand-back.onrender.com"
#define MQTT_PORT 1883
#define MQTT_USERNAME "hotel_system"
#define MQTT_PASSWORD "secure_mqtt_password"
#define MQTT_CLIENT_ID "ESP32_RFID_Reader_001"

// Topics
#define TOPIC_CARD_READ "hotel/rfid/card_read"
#define TOPIC_ACCESS_LOG "hotel/rfid/access_log"
#define TOPIC_SYSTEM_STATUS "hotel/rfid/status"

// Hardware Pins
#define SS_PIN 21
#define RST_PIN 22
#define LED_PIN 2
#define BUZZER_PIN 4

// System Configuration
#define HOTEL_ID "hotel_001"
#define READER_ID "reader_001"
#define LOCATION "Main Entrance"

// Timing Configuration
#define CARD_READ_DELAY 1000
#define WIFI_TIMEOUT 10000
#define MQTT_RECONNECT_DELAY 5000

#endif
```

### **Step 3: Upload and Deploy**

#### **3.1 Compile and Upload**
```cpp
// 1. Open ESP32 code/esp32code.cpp in Arduino IDE
// 2. Select Board: ESP32 Dev Module
// 3. Select Port: COM3 (or your ESP32 port)
// 4. Click Upload
// 5. Monitor Serial Output for debugging
```

#### **3.2 Testing Hardware**
```cpp
// Serial Monitor Output Should Show:
// WiFi connected: 192.168.1.100
// MQTT connected: coastal-grand-back.onrender.com
// RFID reader initialized
// System ready - Place RFID card near reader
```

---

## 🔄 **CI/CD Pipeline**

### **Step 1: GitHub Actions Setup**

#### **1.1 Frontend Workflow**
Create `.github/workflows/deploy-frontend.yml`:

```yaml
name: Deploy Frontend to Vercel

on:
  push:
    branches: [ main ]
    paths: 
      - 'app/**'
      - 'components/**'
      - 'lib/**'
      - 'package.json'

jobs:
  deploy:
    runs-on: ubuntu-latest
    
    steps:
    - uses: actions/checkout@v3
    
    - name: Setup Node.js
      uses: actions/setup-node@v3
      with:
        node-version: '18'
        cache: 'npm'
    
    - name: Install dependencies
      run: npm ci
    
    - name: Build project
      run: npm run build
      env:
        NEXT_PUBLIC_API_URL: ${{ secrets.NEXT_PUBLIC_API_URL }}
        NEXT_PUBLIC_SOCKET_URL: ${{ secrets.NEXT_PUBLIC_SOCKET_URL }}
        
    - name: Deploy to Vercel
      uses: amondnet/vercel-action@v25
      with:
        vercel-token: ${{ secrets.VERCEL_TOKEN }}
        vercel-org-id: ${{ secrets.VERCEL_ORG_ID }}
        vercel-project-id: ${{ secrets.VERCEL_PROJECT_ID }}
        vercel-args: '--prod'
```

#### **1.2 Backend Workflow**
Create `.github/workflows/deploy-backend.yml`:

```yaml
name: Deploy Backend to Render

on:
  push:
    branches: [ main ]
    paths: 
      - 'Backend/**'

jobs:
  deploy:
    runs-on: ubuntu-latest
    
    steps:
    - uses: actions/checkout@v3
    
    - name: Setup Node.js
      uses: actions/setup-node@v3
      with:
        node-version: '18'
        cache: 'npm'
        cache-dependency-path: Backend/package-lock.json
    
    - name: Install dependencies
      run: |
        cd Backend
        npm ci
    
    - name: Run tests
      run: |
        cd Backend
        npm test
      env:
        NODE_ENV: test
        MONGODB_URI: ${{ secrets.MONGODB_URI_TEST }}
        JWT_SECRET: ${{ secrets.JWT_SECRET }}
        
    - name: Deploy to Render
      run: |
        curl -X POST "${{ secrets.RENDER_DEPLOY_HOOK }}"
```

### **Step 2: Required Secrets**

Add these secrets in GitHub repository settings:

```yaml
# Vercel Secrets
VERCEL_TOKEN: your-vercel-token
VERCEL_ORG_ID: your-vercel-org-id
VERCEL_PROJECT_ID: your-vercel-project-id

# Render Secrets
RENDER_DEPLOY_HOOK: your-render-deploy-hook-url

# Environment Secrets
NEXT_PUBLIC_API_URL: https://coastal-grand-back.onrender.com
NEXT_PUBLIC_SOCKET_URL: https://coastal-grand-back.onrender.com
MONGODB_URI: your-mongodb-connection-string
MONGODB_URI_TEST: your-test-mongodb-connection-string
JWT_SECRET: your-jwt-secret-key
```

---

## ✅ **Verification & Testing**

### **Step 1: Deployment Verification**

#### **1.1 Frontend Checks**
```bash
# Test frontend deployment
curl -I https://coastal-grand-tolr.vercel.app
# Expected: HTTP/2 200

# Test API connectivity
curl https://coastal-grand-tolr.vercel.app/api/health
# Expected: {"status":"OK"}
```

#### **1.2 Backend Checks**
```bash
# Test backend deployment
curl -I https://coastal-grand-back.onrender.com
# Expected: HTTP/1.1 200

# Test health endpoint
curl https://coastal-grand-back.onrender.com/health
# Expected: {"status":"OK","timestamp":"..."}

# Test API endpoints
curl -X POST https://coastal-grand-back.onrender.com/api/auth/login \
  -H "Content-Type: application/json" \
  -d '{"email":"admin@hotel.com","password":"admin123"}'
```

#### **1.3 Database Checks**
```javascript
// Test MongoDB connection
const { MongoClient } = require('mongodb');

async function testConnection() {
  const client = new MongoClient(process.env.MONGODB_URI);
  try {
    await client.connect();
    console.log('✅ MongoDB connection successful');
    
    const db = client.db('hotel_management');
    const collections = await db.listCollections().toArray();
    console.log('📊 Collections:', collections.map(c => c.name));
  } finally {
    await client.close();
  }
}
```

### **Step 2: End-to-End Testing**

#### **2.1 User Authentication Flow**
```javascript
// Test complete authentication flow
const testAuth = async () => {
  // 1. Register new user
  const registerResponse = await fetch('/api/auth/register', {
    method: 'POST',
    headers: { 'Content-Type': 'application/json' },
    body: JSON.stringify({
      email: 'test@hotel.com',
      password: 'test123',
      role: 'guest'
    })
  });
  
  // 2. Login user
  const loginResponse = await fetch('/api/auth/login', {
    method: 'POST',
    headers: { 'Content-Type': 'application/json' },
    body: JSON.stringify({
      email: 'test@hotel.com',
      password: 'test123'
    })
  });
  
  const { token } = await loginResponse.json();
  
  // 3. Access protected route
  const protectedResponse = await fetch('/api/hotels', {
    headers: { 'Authorization': `Bearer ${token}` }
  });
  
  console.log('✅ Authentication flow working');
};
```

#### **2.2 RFID Hardware Testing**
```cpp
// ESP32 Serial Monitor Output
void testRFIDSystem() {
  Serial.println("🔧 Testing RFID System...");
  
  // Test WiFi connection
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("✅ WiFi connected");
  }
  
  // Test MQTT connection
  if (mqttClient.connected()) {
    Serial.println("✅ MQTT connected");
  }
  
  // Test RFID reader
  if (mfrc522.PCD_PerformSelfTest()) {
    Serial.println("✅ RFID reader working");
  }
  
  Serial.println("🎯 Place RFID card near reader...");
}
```

### **Step 3: Performance Testing**

#### **3.1 Load Testing**
```bash
# Install artillery for load testing
npm install -g artillery

# Create load test configuration
cat > load-test.yml << EOF
config:
  target: 'https://coastal-grand-back.onrender.com'
  phases:
    - duration: 60
      arrivalRate: 10
scenarios:
  - name: "API Load Test"
    requests:
      - get:
          url: "/health"
      - post:
          url: "/api/auth/login"
          json:
            email: "admin@hotel.com"
            password: "admin123"
EOF

# Run load test
artillery run load-test.yml
```

#### **3.2 Performance Metrics**
```javascript
// Monitor key performance indicators
const performanceMetrics = {
  responseTime: '< 200ms',
  uptime: '99.9%',
  throughput: '100 req/sec',
  errorRate: '< 0.1%',
  memoryUsage: '< 512MB',
  cpuUsage: '< 80%'
};
```

---

## 🔧 **Troubleshooting**

### **Common Deployment Issues**

#### **1. Frontend Issues**

**Build Failures:**
```bash
# Error: Module not found
# Solution: Check import paths and dependencies
npm install
npm run build

# Error: Environment variables not found
# Solution: Verify .env.local configuration
cat .env.local
```

**Vercel Deployment Errors:**
```bash
# Error: Function timeout
# Solution: Optimize API calls and reduce bundle size
npm run analyze

# Error: Build exceeded time limit
# Solution: Enable incremental builds
# Add to next.config.mjs:
experimental: {
  incrementalCacheHandlerPath: require.resolve('./cache-handler.js')
}
```

#### **2. Backend Issues**

**Render Deployment Failures:**
```bash
# Error: Build failed
# Solution: Check package.json and dependencies
cd Backend
npm install
npm start

# Error: Port binding failed
# Solution: Use PORT environment variable
const PORT = process.env.PORT || 3000;
```

**Database Connection Issues:**
```javascript
// Error: MongoNetworkError
// Solution: Check connection string and network access
const mongoose = require('mongoose');

mongoose.connect(process.env.MONGODB_URI, {
  useNewUrlParser: true,
  useUnifiedTopology: true,
  serverSelectionTimeoutMS: 5000,
  socketTimeoutMS: 45000,
});
```

#### **3. Hardware Issues**

**ESP32 Connection Problems:**
```cpp
// WiFi connection failed
// Solution: Check credentials and signal strength
void troubleshootWiFi() {
  Serial.println("WiFi Status: " + String(WiFi.status()));
  Serial.println("Signal Strength: " + String(WiFi.RSSI()));
  
  if (WiFi.status() != WL_CONNECTED) {
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    delay(5000);
  }
}
```

**RFID Reader Issues:**
```cpp
// RFID not detecting cards
// Solution: Check wiring and power supply
void troubleshootRFID() {
  if (!mfrc522.PCD_PerformSelfTest()) {
    Serial.println("❌ RFID reader failed self-test");
    Serial.println("🔧 Check wiring and power supply");
  }
}
```

### **Monitoring and Logs**

#### **Application Monitoring**
```javascript
// Add comprehensive logging
const winston = require('winston');

const logger = winston.createLogger({
  level: 'info',
  format: winston.format.combine(
    winston.format.timestamp(),
    winston.format.json()
  ),
  transports: [
    new winston.transports.File({ filename: 'error.log', level: 'error' }),
    new winston.transports.File({ filename: 'combined.log' })
  ]
});
```

#### **Health Monitoring**
```bash
# Set up monitoring endpoints
curl https://coastal-grand-back.onrender.com/health
curl https://coastal-grand-tolr.vercel.app/api/health

# Monitor system metrics
curl https://coastal-grand-back.onrender.com/metrics
```

---

## 📊 **Deployment Checklist**

### **Pre-Deployment**
- [ ] All environment variables configured
- [ ] Database connection tested
- [ ] Build process successful
- [ ] Tests passing
- [ ] Security configurations verified

### **Deployment**
- [ ] Frontend deployed to Vercel
- [ ] Backend deployed to Render
- [ ] Database configured on MongoDB Atlas
- [ ] ESP32 hardware programmed and tested
- [ ] CI/CD pipeline configured

### **Post-Deployment**
- [ ] All endpoints responding
- [ ] Authentication working
- [ ] Real-time features functional
- [ ] Hardware integration tested
- [ ] Performance metrics within targets
- [ ] Monitoring and logging active

---

## 🎯 **Production URLs**

| Service | URL | Status |
|---------|-----|--------|
| **Frontend** | https://coastal-grand-tolr.vercel.app | ✅ Live |
| **Backend** | https://coastal-grand-back.onrender.com | ✅ Live |
| **API Health** | https://coastal-grand-back.onrender.com/health | ✅ Active |
| **API Docs** | https://coastal-grand-back.onrender.com/api | ✅ Available |

### **Demo Accounts**
```
Administrator:
Email: admin@hotel.com
Password: admin123

Staff Member:
Email: staff@hotel.com
Password: staff123

Guest User:
Email: guest@hotel.com
Password: guest123
```

---

**🎉 Deployment Complete!** Your RFID Hotel Management System is now live and ready for production use.

For additional support, refer to:
- [Environment Setup Guide](ENVIRONMENT_SETUP.md)
- [API Documentation](API_DOCUMENTATION.md)
- [Contributing Guidelines](CONTRIBUTING.md)