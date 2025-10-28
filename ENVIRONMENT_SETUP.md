/**
 * @file ENVIRONMENT_SETUP.md
 * @brief Complete Environment Configuration Guide
 * @author Development Team
 * @version 1.0.0
 * @date 2024
 * 
 * @section env_overview Environment Variables Overview
 * 
 * This document provides comprehensive environment configuration for all components
 * of the RFID Hotel Management System, including missing variables and security recommendations.
 */

# 🔧 Environment Configuration Guide

## 🚨 **CRITICAL ENVIRONMENT ANALYSIS**

### **Current Status Assessment**

Your manager asked to check environment files - here's the complete analysis:

#### ✅ **Files Found**
- `.env` (Frontend root)
- `Backend/.env` (Backend)

#### ⚠️ **Missing Critical Variables**
Several important environment variables are missing for production deployment.

---

## 📋 **Complete Environment Setup**

### **1. Frontend Environment (`.env.local`)**

**Current Configuration:**
```properties
NEXT_PUBLIC_API_URL=https://coastal-grand-back.onrender.com
NEXT_PUBLIC_SOCKET_URL=https://coastal-grand-back.onrender.com
```

**🚨 MISSING VARIABLES - ADD THESE:**
```properties
# Authentication & Security
NEXTAUTH_SECRET=your-super-secret-jwt-key-minimum-32-characters
NEXTAUTH_URL=https://coastal-grand-tolr.vercel.app

# Feature Flags
NEXT_PUBLIC_ENABLE_ANALYTICS=true
NEXT_PUBLIC_ENABLE_REAL_TIME=true
NEXT_PUBLIC_ENABLE_NOTIFICATIONS=true

# Analytics & Monitoring (Optional)
NEXT_PUBLIC_GA_ID=G-XXXXXXXXXX
NEXT_PUBLIC_HOTJAR_ID=your-hotjar-id
NEXT_PUBLIC_SENTRY_DSN=your-sentry-dsn

# Development/Debug
NEXT_PUBLIC_DEBUG_MODE=false
NEXT_PUBLIC_LOG_LEVEL=info

# API Configuration
NEXT_PUBLIC_API_TIMEOUT=30000
NEXT_PUBLIC_WEBSOCKET_TIMEOUT=5000
```

### **2. Backend Environment (`Backend/.env`)**

**Current Configuration:**
```properties
MONGO_URL=mongodb+srv://yahyaimthiyas:23csr243@cluster0.hsasoax.mongodb.net/hotel_db?retryWrites=true&w=majority
PORT=3000
MQTT_PORT=1883
FRONTEND_URL=https://coastal-grand-tolr.vercel.app
```

**🚨 MISSING CRITICAL VARIABLES - ADD THESE:**
```properties
# Node Environment
NODE_ENV=production

# Security Keys (GENERATE NEW ONES!)
JWT_SECRET=your-jwt-secret-key-minimum-32-characters-long
SESSION_SECRET=your-session-secret-key-minimum-32-characters
ENCRYPTION_KEY=your-32-character-encryption-key-here
COOKIE_SECRET=your-cookie-secret-key-minimum-32-chars

# CORS Configuration
CORS_ORIGINS=https://coastal-grand-tolr.vercel.app,http://localhost:3000,http://localhost:3001

# Rate Limiting
RATE_LIMIT_WINDOW_MS=900000
RATE_LIMIT_MAX_REQUESTS=100
RATE_LIMIT_SKIP_SUCCESSFUL_REQUESTS=true

# Database Configuration
DB_MAX_POOL_SIZE=10
DB_SERVER_SELECTION_TIMEOUT=5000
DB_SOCKET_TIMEOUT=45000

# Email Configuration (for notifications)
SMTP_HOST=smtp.gmail.com
SMTP_PORT=587
SMTP_SECURE=false
SMTP_USER=your-email@gmail.com
SMTP_PASS=your-app-specific-password

# Monitoring & Logging
LOG_LEVEL=info
SENTRY_DSN=your-sentry-dsn-for-error-tracking
ENABLE_REQUEST_LOGGING=true

# WebSocket Configuration
WS_HEARTBEAT_INTERVAL=30000
WS_HEARTBEAT_TIMEOUT=5000
WS_MAX_CONNECTIONS=1000

# MQTT Configuration
MQTT_KEEP_ALIVE=60
MQTT_CONNECT_TIMEOUT=30000
MQTT_RECONNECT_PERIOD=1000

# File Upload (if needed)
MAX_FILE_SIZE=10485760
UPLOAD_PATH=./uploads
ALLOWED_FILE_TYPES=jpg,jpeg,png,pdf

# Cache Configuration
REDIS_URL=redis://localhost:6379
CACHE_TTL=3600

# Backup Configuration
BACKUP_ENABLED=true
BACKUP_SCHEDULE=0 2 * * *
BACKUP_RETENTION_DAYS=30
```

### **3. ESP32 Configuration (`ESP32 code/config.h`)**

**Create this new file:**
```cpp
/**
 * @file config.h
 * @brief ESP32 Configuration Header
 * @author Hardware Team
 * @version 1.0.0
 */

#ifndef CONFIG_H
#define CONFIG_H

// WiFi Configuration
#define WIFI_SSID "YOUR_WIFI_NETWORK_NAME"
#define WIFI_PASSWORD "YOUR_WIFI_PASSWORD"
#define WIFI_TIMEOUT 15000
#define WIFI_RETRY_DELAY 500

// Server Configuration
#define WEBSOCKET_HOST "coastal-grand-back.onrender.com"
#define WEBSOCKET_PORT 443
#define WEBSOCKET_PATH "/mqtt"
#define WEBSOCKET_PROTOCOL "wss"

// Room Configuration (CHANGE FOR EACH DEVICE)
#define ROOM_NUMBER "202"
#define BUILDING_ID "main"
#define FLOOR_NUMBER "3"  // This maps to hotelId (1-8)
#define HOTEL_NAME "Coastal Grand Hotel - Yercaud"

// Hardware Pins
#define RFID_RST_PIN 22
#define RFID_SS_PIN 21
#define LED_PIN 2
#define BUZZER_PIN 4

// RFID Configuration
#define CARD_ABSENT_THRESHOLD 5
#define CARD_READ_DELAY 100
#define MAX_USERS 50

// NTP Configuration
#define NTP_SERVER1 "pool.ntp.org"
#define NTP_SERVER2 "time.nist.gov"
#define NTP_SERVER3 "time.google.com"
#define GMT_OFFSET_SEC 19800  // IST +5:30
#define DAYLIGHT_OFFSET_SEC 0
#define NTP_SYNC_INTERVAL 3600000  // 1 hour

// WebSocket Configuration
#define WS_RECONNECT_INTERVAL 5000
#define WS_HEARTBEAT_INTERVAL 15000
#define WS_HEARTBEAT_TIMEOUT 3000
#define WS_MAX_RETRY_COUNT 2

// Debug Configuration
#define DEBUG_MODE true
#define SERIAL_BAUD_RATE 115200
#define DEBUG_RFID false
#define DEBUG_WEBSOCKET true
#define DEBUG_MQTT true

// Security Configuration
#define ENABLE_ENCRYPTION false
#define DEVICE_ID "ESP32_ROOM_202_HOTEL_3"
#define FIRMWARE_VERSION "1.0.0"

#endif // CONFIG_H
```

---

## 🔐 **Security Recommendations**

### **1. Generate Secure Keys**

**Use these commands to generate secure keys:**

```bash
# Generate JWT Secret (32+ characters)
openssl rand -base64 32

# Generate Session Secret
openssl rand -hex 32

# Generate Encryption Key (exactly 32 characters)
openssl rand -hex 16

# Generate Cookie Secret
openssl rand -base64 32
```

### **2. Environment File Security**

```bash
# Set proper file permissions
chmod 600 .env
chmod 600 Backend/.env

# Add to .gitignore
echo ".env*" >> .gitignore
echo "!.env.example" >> .gitignore
```

### **3. Create Example Files**

**`.env.example`:**
```properties
# API Configuration
NEXT_PUBLIC_API_URL=https://your-backend-url.com
NEXT_PUBLIC_SOCKET_URL=https://your-backend-url.com

# Authentication
NEXTAUTH_SECRET=your-secret-key-here
NEXTAUTH_URL=https://your-frontend-url.com

# Features
NEXT_PUBLIC_ENABLE_ANALYTICS=true
NEXT_PUBLIC_ENABLE_REAL_TIME=true
```

**`Backend/.env.example`:**
```properties
# Database
MONGO_URL=mongodb+srv://user:pass@cluster.mongodb.net/hotel_db

# Server
PORT=3000
NODE_ENV=production

# Security
JWT_SECRET=your-jwt-secret-here
SESSION_SECRET=your-session-secret-here

# Frontend
FRONTEND_URL=https://your-frontend-url.com
```

---

## 🚀 **Deployment-Specific Configurations**

### **Vercel (Frontend)**

**Environment Variables in Vercel Dashboard:**
```properties
NEXT_PUBLIC_API_URL=https://coastal-grand-back.onrender.com
NEXT_PUBLIC_SOCKET_URL=https://coastal-grand-back.onrender.com
NEXTAUTH_SECRET=your-generated-secret-key
NEXTAUTH_URL=https://coastal-grand-tolr.vercel.app
NEXT_PUBLIC_ENABLE_ANALYTICS=true
NEXT_PUBLIC_ENABLE_REAL_TIME=true
```

### **Render (Backend)**

**Environment Variables in Render Dashboard:**
```properties
MONGO_URL=mongodb+srv://yahyaimthiyas:23csr243@cluster0.hsasoax.mongodb.net/hotel_db?retryWrites=true&w=majority
PORT=3000
NODE_ENV=production
JWT_SECRET=your-generated-jwt-secret
SESSION_SECRET=your-generated-session-secret
FRONTEND_URL=https://coastal-grand-tolr.vercel.app
CORS_ORIGINS=https://coastal-grand-tolr.vercel.app,http://localhost:3000
RATE_LIMIT_WINDOW_MS=900000
RATE_LIMIT_MAX_REQUESTS=100
LOG_LEVEL=info
```

---

## 🧪 **Environment Validation**

### **1. Frontend Validation Script**

**Create `scripts/validate-env.js`:**
```javascript
/**
 * @brief Environment validation script
 * @file scripts/validate-env.js
 */

const requiredEnvVars = [
  'NEXT_PUBLIC_API_URL',
  'NEXT_PUBLIC_SOCKET_URL',
  'NEXTAUTH_SECRET',
  'NEXTAUTH_URL'
];

const optionalEnvVars = [
  'NEXT_PUBLIC_GA_ID',
  'NEXT_PUBLIC_SENTRY_DSN',
  'NEXT_PUBLIC_ENABLE_ANALYTICS'
];

console.log('🔍 Validating Frontend Environment Variables...\n');

let missingRequired = [];
let missingOptional = [];

// Check required variables
requiredEnvVars.forEach(varName => {
  if (!process.env[varName]) {
    missingRequired.push(varName);
  } else {
    console.log(`✅ ${varName}: ${process.env[varName].substring(0, 20)}...`);
  }
});

// Check optional variables
optionalEnvVars.forEach(varName => {
  if (!process.env[varName]) {
    missingOptional.push(varName);
  } else {
    console.log(`✅ ${varName}: ${process.env[varName]}`);
  }
});

// Report results
if (missingRequired.length > 0) {
  console.log('\n❌ Missing Required Variables:');
  missingRequired.forEach(varName => {
    console.log(`   - ${varName}`);
  });
  process.exit(1);
}

if (missingOptional.length > 0) {
  console.log('\n⚠️  Missing Optional Variables:');
  missingOptional.forEach(varName => {
    console.log(`   - ${varName}`);
  });
}

console.log('\n✅ Environment validation passed!');
```

### **2. Backend Validation Script**

**Create `Backend/scripts/validate-env.js`:**
```javascript
/**
 * @brief Backend environment validation
 * @file Backend/scripts/validate-env.js
 */

const requiredEnvVars = [
  'MONGO_URL',
  'PORT',
  'NODE_ENV',
  'JWT_SECRET',
  'SESSION_SECRET',
  'FRONTEND_URL'
];

const securityEnvVars = [
  'JWT_SECRET',
  'SESSION_SECRET',
  'ENCRYPTION_KEY'
];

console.log('🔍 Validating Backend Environment Variables...\n');

let missingRequired = [];
let weakSecrets = [];

// Check required variables
requiredEnvVars.forEach(varName => {
  if (!process.env[varName]) {
    missingRequired.push(varName);
  } else {
    console.log(`✅ ${varName}: ${varName.includes('SECRET') ? '[HIDDEN]' : process.env[varName]}`);
  }
});

// Check security variables strength
securityEnvVars.forEach(varName => {
  const value = process.env[varName];
  if (value && value.length < 32) {
    weakSecrets.push(varName);
  }
});

// Report results
if (missingRequired.length > 0) {
  console.log('\n❌ Missing Required Variables:');
  missingRequired.forEach(varName => {
    console.log(`   - ${varName}`);
  });
}

if (weakSecrets.length > 0) {
  console.log('\n⚠️  Weak Security Keys (should be 32+ characters):');
  weakSecrets.forEach(varName => {
    console.log(`   - ${varName}: ${process.env[varName]?.length || 0} characters`);
  });
}

if (missingRequired.length > 0 || weakSecrets.length > 0) {
  process.exit(1);
}

console.log('\n✅ Backend environment validation passed!');
```

### **3. Run Validation**

```bash
# Frontend validation
node scripts/validate-env.js

# Backend validation
cd Backend
node scripts/validate-env.js
```

---

## 🔄 **Environment Management**

### **1. Development vs Production**

**Development (`.env.local`):**
```properties
NEXT_PUBLIC_API_URL=http://localhost:3000
NEXT_PUBLIC_SOCKET_URL=http://localhost:3000
NEXT_PUBLIC_DEBUG_MODE=true
NEXT_PUBLIC_LOG_LEVEL=debug
```

**Production (Vercel):**
```properties
NEXT_PUBLIC_API_URL=https://coastal-grand-back.onrender.com
NEXT_PUBLIC_SOCKET_URL=https://coastal-grand-back.onrender.com
NEXT_PUBLIC_DEBUG_MODE=false
NEXT_PUBLIC_LOG_LEVEL=error
```

### **2. Environment Loading Order**

Next.js loads environment variables in this order:
1. `.env.local` (always loaded, ignored by git)
2. `.env.production` or `.env.development`
3. `.env`

### **3. Environment Variable Types**

- **`NEXT_PUBLIC_*`**: Exposed to browser
- **Regular variables**: Server-side only
- **System variables**: Set by hosting platform

---

## 📊 **Environment Monitoring**

### **1. Health Check Endpoint**

**Add to `Backend/index.js`:**
```javascript
/**
 * @brief Environment health check endpoint
 * @route GET /api/health/env
 */
app.get('/api/health/env', (req, res) => {
  const envStatus = {
    timestamp: new Date().toISOString(),
    environment: process.env.NODE_ENV,
    database: process.env.MONGO_URL ? 'configured' : 'missing',
    jwt: process.env.JWT_SECRET ? 'configured' : 'missing',
    cors: process.env.CORS_ORIGINS ? 'configured' : 'missing',
    frontend: process.env.FRONTEND_URL ? 'configured' : 'missing',
    port: process.env.PORT || 3000,
    version: process.env.npm_package_version || '1.0.0'
  };
  
  res.json(envStatus);
});
```

### **2. Environment Dashboard**

**Create monitoring dashboard at `/admin/env`:**
```typescript
/**
 * @brief Environment monitoring component
 * @component EnvironmentDashboard
 */
export function EnvironmentDashboard() {
  const [envStatus, setEnvStatus] = useState(null);
  
  useEffect(() => {
    fetch('/api/health/env')
      .then(res => res.json())
      .then(setEnvStatus);
  }, []);
  
  return (
    <div className="p-6">
      <h2 className="text-2xl font-bold mb-4">Environment Status</h2>
      {envStatus && (
        <div className="grid grid-cols-2 gap-4">
          {Object.entries(envStatus).map(([key, value]) => (
            <div key={key} className="p-4 border rounded">
              <div className="font-medium">{key}</div>
              <div className={`text-sm ${
                value === 'configured' ? 'text-green-600' : 
                value === 'missing' ? 'text-red-600' : 'text-gray-600'
              }`}>
                {typeof value === 'string' && value.length > 50 
                  ? `${value.substring(0, 50)}...` 
                  : String(value)
                }
              </div>
            </div>
          ))}
        </div>
      )}
    </div>
  );
}
```

---

## 🚨 **Action Items for Your Manager**

### **Immediate Actions Required:**

1. **🔐 Generate Security Keys**
   ```bash
   # Run these commands and add to environment
   openssl rand -base64 32  # For JWT_SECRET
   openssl rand -base64 32  # For SESSION_SECRET
   openssl rand -hex 16     # For ENCRYPTION_KEY
   ```

2. **📝 Add Missing Variables**
   - Add all missing variables listed above
   - Update deployment platforms (Vercel/Render)
   - Test all environments

3. **🧪 Validate Configuration**
   ```bash
   # Run validation scripts
   node scripts/validate-env.js
   cd Backend && node scripts/validate-env.js
   ```

4. **🔒 Secure Environment Files**
   ```bash
   # Set proper permissions
   chmod 600 .env*
   
   # Verify .gitignore
   echo ".env*" >> .gitignore
   ```

5. **📊 Monitor Environment**
   - Set up environment monitoring
   - Create alerts for missing variables
   - Regular security key rotation

### **Priority Level: HIGH** 🚨

The missing environment variables could cause:
- Authentication failures
- Security vulnerabilities  
- Production deployment issues
- CORS errors
- Rate limiting problems

**Estimated Time to Fix: 2-3 hours**

---

**Last Updated**: December 2024  
**Status**: Action Required ⚠️  
**Priority**: HIGH 🚨