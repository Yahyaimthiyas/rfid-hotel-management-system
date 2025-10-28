/**
 * @file GITHUB_REPOSITORY_SETUP.md
 * @brief Complete GitHub Repository Setup Guide
 * @author Development Team
 * @version 1.0.0
 * @date 2024
 * 
 * @section repo_overview Repository Structure
 * 
 * This document provides step-by-step instructions for setting up the complete
 * RFID Hotel Management System repository on GitHub with all deployment procedures.
 */

# 🚀 GitHub Repository Setup Guide

## 📋 **Repository Information**

**Repository Name**: `rfid-hotel-management-system`  
**Description**: Complete RFID Hotel Management System with ESP32 integration, real-time monitoring, and advanced analytics  
**Visibility**: Public (or Private based on requirements)  
**License**: MIT License  

---

## 🏗️ **Complete Repository Structure**

```
rfid-hotel-management-system/
├── 📁 Frontend/
│   ├── 📁 app/
│   │   ├── 📁 dashboard/
│   │   ├── 📁 login/
│   │   ├── layout.tsx
│   │   ├── page.tsx
│   │   └── globals.css
│   ├── 📁 components/
│   │   ├── 📁 auth/
│   │   ├── 📁 dashboards/
│   │   └── 📁 ui/
│   ├── 📁 lib/
│   ├── 📁 hooks/
│   ├── package.json
│   ├── next.config.mjs
│   ├── tailwind.config.ts
│   └── tsconfig.json
├── 📁 Backend/
│   ├── index.js
│   ├── package.json
│   ├── .env.example
│   └── 📁 scripts/
├── 📁 ESP32_Code/
│   ├── esp32code.cpp
│   ├── config.h
│   ├── README.md
│   └── 📁 libraries/
├── 📁 Documentation/
│   ├── DEPLOYMENT_GUIDE.md
│   ├── ENVIRONMENT_SETUP.md
│   ├── API_DOCUMENTATION.md
│   └── TROUBLESHOOTING.md
├── 📁 Scripts/
│   ├── deploy.sh
│   ├── setup.sh
│   └── validate-env.js
├── 📁 .github/
│   ├── 📁 workflows/
│   │   ├── deploy-frontend.yml
│   │   ├── deploy-backend.yml
│   │   └── test.yml
│   ├── ISSUE_TEMPLATE.md
│   └── PULL_REQUEST_TEMPLATE.md
├── README.md
├── LICENSE
├── .gitignore
├── .env.example
└── package.json
```

---

## 🔧 **Step-by-Step Setup**

### **Step 1: Create GitHub Repository**

```bash
# Create new repository on GitHub
# Repository name: rfid-hotel-management-system
# Description: Complete RFID Hotel Management System with ESP32 integration
# Visibility: Public
# Initialize with README: No (we'll add our own)
```

### **Step 2: Clone and Setup Local Repository**

```bash
# Clone the empty repository
git clone https://github.com/YOUR_USERNAME/rfid-hotel-management-system.git
cd rfid-hotel-management-system

# Initialize git if not already done
git init
git remote add origin https://github.com/YOUR_USERNAME/rfid-hotel-management-system.git
```

### **Step 3: Create Repository Structure**

```bash
# Create main directories
mkdir -p Frontend Backend ESP32_Code Documentation Scripts .github/workflows

# Move existing files to proper structure
# (Assuming you have the current project files)
```

### **Step 4: Create Essential Files**

#### **`.gitignore`**
```gitignore
# Dependencies
node_modules/
npm-debug.log*
yarn-debug.log*
yarn-error.log*

# Environment variables
.env
.env.local
.env.development.local
.env.test.local
.env.production.local
Backend/.env

# Next.js
.next/
out/
build/

# Production builds
dist/
*.tgz

# Runtime data
pids
*.pid
*.seed
*.pid.lock

# Coverage directory used by tools like istanbul
coverage/
*.lcov

# nyc test coverage
.nyc_output

# Dependency directories
jspm_packages/

# Optional npm cache directory
.npm

# Optional eslint cache
.eslintcache

# Microbundle cache
.rpt2_cache/
.rts2_cache_cjs/
.rts2_cache_es/
.rts2_cache_umd/

# Optional REPL history
.node_repl_history

# Output of 'npm pack'
*.tgz

# Yarn Integrity file
.yarn-integrity

# parcel-bundler cache (https://parceljs.org/)
.cache
.parcel-cache

# Next.js build output
.next

# Nuxt.js build / generate output
.nuxt
dist

# Gatsby files
.cache/
public

# Storybook build outputs
.out
.storybook-out

# Temporary folders
tmp/
temp/

# Editor directories and files
.vscode/
.idea/
*.swp
*.swo
*~

# OS generated files
.DS_Store
.DS_Store?
._*
.Spotlight-V100
.Trashes
ehthumbs.db
Thumbs.db

# Logs
logs
*.log

# Database
*.db
*.sqlite

# Uploads
uploads/

# ESP32 specific
*.bin
*.elf
*.map

# Arduino IDE
*.ino.bak
```

#### **`LICENSE`**
```
MIT License

Copyright (c) 2024 RFID Hotel Management System

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```

#### **Root `package.json`**
```json
{
  "name": "rfid-hotel-management-system",
  "version": "1.0.0",
  "description": "Complete RFID Hotel Management System with ESP32 integration, real-time monitoring, and advanced analytics",
  "main": "index.js",
  "scripts": {
    "dev": "concurrently \"npm run dev:frontend\" \"npm run dev:backend\"",
    "dev:frontend": "cd Frontend && npm run dev",
    "dev:backend": "cd Backend && npm start",
    "build": "npm run build:frontend",
    "build:frontend": "cd Frontend && npm run build",
    "start": "npm run start:frontend",
    "start:frontend": "cd Frontend && npm start",
    "install:all": "npm install && cd Frontend && npm install && cd ../Backend && npm install",
    "test": "npm run test:frontend && npm run test:backend",
    "test:frontend": "cd Frontend && npm test",
    "test:backend": "cd Backend && npm test",
    "lint": "npm run lint:frontend && npm run lint:backend",
    "lint:frontend": "cd Frontend && npm run lint",
    "lint:backend": "cd Backend && npm run lint",
    "validate-env": "node Scripts/validate-env.js",
    "setup": "chmod +x Scripts/setup.sh && ./Scripts/setup.sh",
    "deploy": "chmod +x Scripts/deploy.sh && ./Scripts/deploy.sh"
  },
  "keywords": [
    "rfid",
    "hotel-management",
    "esp32",
    "iot",
    "nextjs",
    "nodejs",
    "mongodb",
    "real-time",
    "analytics",
    "dashboard"
  ],
  "author": "Development Team",
  "license": "MIT",
  "repository": {
    "type": "git",
    "url": "https://github.com/YOUR_USERNAME/rfid-hotel-management-system.git"
  },
  "bugs": {
    "url": "https://github.com/YOUR_USERNAME/rfid-hotel-management-system/issues"
  },
  "homepage": "https://github.com/YOUR_USERNAME/rfid-hotel-management-system#readme",
  "devDependencies": {
    "concurrently": "^8.2.2"
  }
}
```

---

## 🚀 **GitHub Actions Workflows**

### **`.github/workflows/deploy-frontend.yml`**
```yaml
name: Deploy Frontend to Vercel

on:
  push:
    branches: [ main ]
    paths: [ 'Frontend/**' ]
  pull_request:
    branches: [ main ]
    paths: [ 'Frontend/**' ]

jobs:
  deploy:
    runs-on: ubuntu-latest
    
    steps:
    - name: Checkout code
      uses: actions/checkout@v4
      
    - name: Setup Node.js
      uses: actions/setup-node@v4
      with:
        node-version: '18'
        cache: 'npm'
        cache-dependency-path: Frontend/package-lock.json
        
    - name: Install dependencies
      run: |
        cd Frontend
        npm ci
        
    - name: Run tests
      run: |
        cd Frontend
        npm test -- --coverage --watchAll=false
        
    - name: Build application
      run: |
        cd Frontend
        npm run build
      env:
        NEXT_PUBLIC_API_URL: ${{ secrets.NEXT_PUBLIC_API_URL }}
        NEXT_PUBLIC_SOCKET_URL: ${{ secrets.NEXT_PUBLIC_SOCKET_URL }}
        
    - name: Deploy to Vercel
      uses: amondnet/vercel-action@v25
      with:
        vercel-token: ${{ secrets.VERCEL_TOKEN }}
        vercel-org-id: ${{ secrets.VERCEL_ORG_ID }}
        vercel-project-id: ${{ secrets.VERCEL_PROJECT_ID }}
        working-directory: Frontend
        vercel-args: '--prod'
```

### **`.github/workflows/deploy-backend.yml`**
```yaml
name: Deploy Backend to Render

on:
  push:
    branches: [ main ]
    paths: [ 'Backend/**' ]
  pull_request:
    branches: [ main ]
    paths: [ 'Backend/**' ]

jobs:
  deploy:
    runs-on: ubuntu-latest
    
    steps:
    - name: Checkout code
      uses: actions/checkout@v4
      
    - name: Setup Node.js
      uses: actions/setup-node@v4
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
        MONGO_URL: ${{ secrets.MONGO_URL_TEST }}
        JWT_SECRET: ${{ secrets.JWT_SECRET }}
        
    - name: Deploy to Render
      run: |
        curl -X POST "${{ secrets.RENDER_DEPLOY_HOOK }}"
```

### **`.github/workflows/test.yml`**
```yaml
name: Run Tests

on:
  push:
    branches: [ main, develop ]
  pull_request:
    branches: [ main, develop ]

jobs:
  test-frontend:
    runs-on: ubuntu-latest
    
    steps:
    - uses: actions/checkout@v4
    
    - name: Setup Node.js
      uses: actions/setup-node@v4
      with:
        node-version: '18'
        cache: 'npm'
        cache-dependency-path: Frontend/package-lock.json
        
    - name: Install dependencies
      run: |
        cd Frontend
        npm ci
        
    - name: Run linting
      run: |
        cd Frontend
        npm run lint
        
    - name: Run tests
      run: |
        cd Frontend
        npm test -- --coverage --watchAll=false
        
    - name: Upload coverage to Codecov
      uses: codecov/codecov-action@v3
      with:
        directory: Frontend/coverage
        
  test-backend:
    runs-on: ubuntu-latest
    
    services:
      mongodb:
        image: mongo:5.0
        ports:
          - 27017:27017
          
    steps:
    - uses: actions/checkout@v4
    
    - name: Setup Node.js
      uses: actions/setup-node@v4
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
        MONGO_URL: mongodb://localhost:27017/hotel_test
        JWT_SECRET: test-secret-key
        NODE_ENV: test
```

---

## 📝 **GitHub Templates**

### **`.github/ISSUE_TEMPLATE.md`**
```markdown
---
name: Bug Report / Feature Request
about: Create a report to help us improve
title: '[BUG/FEATURE] Brief description'
labels: ''
assignees: ''
---

## Issue Type
- [ ] Bug Report
- [ ] Feature Request
- [ ] Documentation Update
- [ ] Question

## Description
A clear and concise description of what the issue is.

## Steps to Reproduce (for bugs)
1. Go to '...'
2. Click on '....'
3. Scroll down to '....'
4. See error

## Expected Behavior
A clear and concise description of what you expected to happen.

## Actual Behavior
A clear and concise description of what actually happened.

## Screenshots
If applicable, add screenshots to help explain your problem.

## Environment
- **OS**: [e.g. Windows 10, macOS, Ubuntu]
- **Browser**: [e.g. Chrome, Firefox, Safari]
- **Node.js Version**: [e.g. 18.17.0]
- **Component**: [Frontend/Backend/ESP32]

## Additional Context
Add any other context about the problem here.

## Possible Solution
If you have ideas on how to fix this, please describe them here.
```

### **`.github/PULL_REQUEST_TEMPLATE.md`**
```markdown
## Description
Brief description of changes made in this PR.

## Type of Change
- [ ] Bug fix (non-breaking change which fixes an issue)
- [ ] New feature (non-breaking change which adds functionality)
- [ ] Breaking change (fix or feature that would cause existing functionality to not work as expected)
- [ ] Documentation update
- [ ] Performance improvement
- [ ] Code refactoring

## Testing
- [ ] Tests pass locally
- [ ] Added new tests for new functionality
- [ ] Updated existing tests
- [ ] Manual testing completed

## Checklist
- [ ] My code follows the project's style guidelines
- [ ] I have performed a self-review of my own code
- [ ] I have commented my code, particularly in hard-to-understand areas
- [ ] I have made corresponding changes to the documentation
- [ ] My changes generate no new warnings
- [ ] I have added tests that prove my fix is effective or that my feature works
- [ ] New and existing unit tests pass locally with my changes

## Screenshots (if applicable)
Add screenshots to help explain your changes.

## Related Issues
Closes #(issue number)

## Additional Notes
Any additional information or context about the PR.
```

---

## 🔧 **Setup Scripts**

### **`Scripts/setup.sh`**
```bash
#!/bin/bash

/**
 * @file setup.sh
 * @brief Complete project setup script
 * @author Development Team
 * @version 1.0.0
 */

echo "🚀 Setting up RFID Hotel Management System..."

# Check if Node.js is installed
if ! command -v node &> /dev/null; then
    echo "❌ Node.js is not installed. Please install Node.js 18+ first."
    exit 1
fi

# Check Node.js version
NODE_VERSION=$(node -v | cut -d'v' -f2 | cut -d'.' -f1)
if [ "$NODE_VERSION" -lt 18 ]; then
    echo "❌ Node.js version 18+ required. Current version: $(node -v)"
    exit 1
fi

echo "✅ Node.js version: $(node -v)"

# Install root dependencies
echo "📦 Installing root dependencies..."
npm install

# Install frontend dependencies
echo "📦 Installing frontend dependencies..."
cd Frontend
npm install
cd ..

# Install backend dependencies
echo "📦 Installing backend dependencies..."
cd Backend
npm install
cd ..

# Create environment files from examples
echo "🔧 Setting up environment files..."

if [ ! -f ".env.local" ]; then
    if [ -f ".env.example" ]; then
        cp .env.example .env.local
        echo "✅ Created .env.local from example"
    else
        echo "⚠️  No .env.example found. Please create .env.local manually."
    fi
fi

if [ ! -f "Backend/.env" ]; then
    if [ -f "Backend/.env.example" ]; then
        cp Backend/.env.example Backend/.env
        echo "✅ Created Backend/.env from example"
    else
        echo "⚠️  No Backend/.env.example found. Please create Backend/.env manually."
    fi
fi

# Set proper permissions
chmod 600 .env* 2>/dev/null || true
chmod 600 Backend/.env* 2>/dev/null || true

# Validate environment
echo "🔍 Validating environment..."
node Scripts/validate-env.js

echo "✅ Setup completed successfully!"
echo ""
echo "🚀 Next steps:"
echo "1. Update environment variables in .env.local and Backend/.env"
echo "2. Run 'npm run dev' to start development servers"
echo "3. Visit http://localhost:3000 to see the application"
echo ""
echo "📚 Documentation:"
echo "- README.md - Project overview"
echo "- Documentation/DEPLOYMENT_GUIDE.md - Deployment instructions"
echo "- Documentation/ENVIRONMENT_SETUP.md - Environment configuration"
```

### **`Scripts/deploy.sh`**
```bash
#!/bin/bash

/**
 * @file deploy.sh
 * @brief Deployment script for production
 * @author Development Team
 * @version 1.0.0
 */

echo "🚀 Deploying RFID Hotel Management System..."

# Validate environment
echo "🔍 Validating environment..."
node Scripts/validate-env.js
if [ $? -ne 0 ]; then
    echo "❌ Environment validation failed. Please fix environment variables."
    exit 1
fi

# Build frontend
echo "🏗️  Building frontend..."
cd Frontend
npm run build
if [ $? -ne 0 ]; then
    echo "❌ Frontend build failed."
    exit 1
fi
cd ..

# Test backend
echo "🧪 Testing backend..."
cd Backend
npm test
if [ $? -ne 0 ]; then
    echo "❌ Backend tests failed."
    exit 1
fi
cd ..

echo "✅ All checks passed!"

# Deploy to Vercel (frontend)
echo "🚀 Deploying frontend to Vercel..."
cd Frontend
npx vercel --prod
cd ..

# Deploy to Render (backend)
echo "🚀 Triggering backend deployment on Render..."
if [ -n "$RENDER_DEPLOY_HOOK" ]; then
    curl -X POST "$RENDER_DEPLOY_HOOK"
    echo "✅ Backend deployment triggered"
else
    echo "⚠️  RENDER_DEPLOY_HOOK not set. Please deploy backend manually."
fi

echo "✅ Deployment completed!"
```

### **`Scripts/validate-env.js`**
```javascript
/**
 * @file validate-env.js
 * @brief Environment validation script
 * @author Development Team
 * @version 1.0.0
 */

const fs = require('fs');
const path = require('path');

console.log('🔍 Validating Environment Configuration...\n');

// Frontend environment validation
const frontendEnvPath = path.join(__dirname, '..', '.env.local');
const frontendRequired = [
    'NEXT_PUBLIC_API_URL',
    'NEXT_PUBLIC_SOCKET_URL'
];

console.log('📱 Frontend Environment:');
if (fs.existsSync(frontendEnvPath)) {
    const frontendEnv = fs.readFileSync(frontendEnvPath, 'utf8');
    let frontendMissing = [];
    
    frontendRequired.forEach(varName => {
        if (!frontendEnv.includes(varName)) {
            frontendMissing.push(varName);
        } else {
            console.log(`   ✅ ${varName}`);
        }
    });
    
    if (frontendMissing.length > 0) {
        console.log('   ❌ Missing variables:');
        frontendMissing.forEach(varName => {
            console.log(`      - ${varName}`);
        });
    }
} else {
    console.log('   ❌ .env.local not found');
}

// Backend environment validation
const backendEnvPath = path.join(__dirname, '..', 'Backend', '.env');
const backendRequired = [
    'MONGO_URL',
    'PORT',
    'JWT_SECRET',
    'FRONTEND_URL'
];

console.log('\n🖥️  Backend Environment:');
if (fs.existsSync(backendEnvPath)) {
    const backendEnv = fs.readFileSync(backendEnvPath, 'utf8');
    let backendMissing = [];
    
    backendRequired.forEach(varName => {
        if (!backendEnv.includes(varName)) {
            backendMissing.push(varName);
        } else {
            console.log(`   ✅ ${varName}`);
        }
    });
    
    if (backendMissing.length > 0) {
        console.log('   ❌ Missing variables:');
        backendMissing.forEach(varName => {
            console.log(`      - ${varName}`);
        });
    }
} else {
    console.log('   ❌ Backend/.env not found');
}

console.log('\n✅ Environment validation completed!');
console.log('\n📚 For detailed environment setup, see:');
console.log('   Documentation/ENVIRONMENT_SETUP.md');
```

---

## 📚 **Documentation Structure**

### **`Documentation/API_DOCUMENTATION.md`**
```markdown
# API Documentation

## Base URL
- Production: `https://coastal-grand-back.onrender.com`
- Development: `http://localhost:3000`

## Authentication
All API endpoints require authentication via JWT token.

### Login
```http
POST /api/auth/login
Content-Type: application/json

{
  "email": "admin@hotel.com",
  "password": "admin123"
}
```

## Hotels API

### Get All Hotels
```http
GET /api/hotels
Authorization: Bearer <token>
```

### Get Hotel by ID
```http
GET /api/hotel/:hotelId
Authorization: Bearer <token>
```

[Continue with full API documentation...]
```

### **`Documentation/TROUBLESHOOTING.md`**
```markdown
# Troubleshooting Guide

## Common Issues

### 1. Environment Variables Not Loading
**Problem**: Environment variables are undefined
**Solution**: 
- Check file names (.env.local for frontend, .env for backend)
- Restart development servers
- Verify file permissions

### 2. CORS Errors
**Problem**: Cross-origin requests blocked
**Solution**:
- Update CORS_ORIGINS in backend .env
- Check frontend API URL configuration

[Continue with troubleshooting guide...]
```

---

## 🔐 **Repository Secrets**

### **GitHub Secrets to Add**

Go to Repository Settings → Secrets and Variables → Actions:

```
# Vercel Deployment
VERCEL_TOKEN=your-vercel-token
VERCEL_ORG_ID=your-org-id
VERCEL_PROJECT_ID=your-project-id

# Render Deployment
RENDER_DEPLOY_HOOK=your-render-deploy-hook-url

# Environment Variables
NEXT_PUBLIC_API_URL=https://coastal-grand-back.onrender.com
NEXT_PUBLIC_SOCKET_URL=https://coastal-grand-back.onrender.com
MONGO_URL=your-mongodb-connection-string
JWT_SECRET=your-jwt-secret
MONGO_URL_TEST=mongodb://localhost:27017/hotel_test
```

---

## 🚀 **Final Repository Setup**

### **Step 5: Initial Commit**

```bash
# Add all files
git add .

# Initial commit
git commit -m "feat: initial commit - complete RFID hotel management system

- Add Next.js 15 frontend with TypeScript
- Add Node.js/Express backend with MongoDB
- Add ESP32 RFID integration code
- Add comprehensive documentation
- Add GitHub Actions workflows
- Add deployment scripts and configurations
- Add environment validation
- Add complete project structure"

# Push to GitHub
git push -u origin main
```

### **Step 6: Create Branches**

```bash
# Create development branch
git checkout -b develop
git push -u origin develop

# Create feature branch template
git checkout -b feature/example-feature
git push -u origin feature/example-feature
git checkout main
```

### **Step 7: Repository Settings**

1. **Branch Protection Rules**:
   - Protect `main` branch
   - Require pull request reviews
   - Require status checks to pass

2. **Repository Topics**:
   ```
   rfid, hotel-management, esp32, iot, nextjs, nodejs, 
   mongodb, real-time, analytics, dashboard, typescript
   ```

3. **Repository Description**:
   ```
   Complete RFID Hotel Management System with ESP32 integration, 
   real-time monitoring, and advanced analytics dashboard
   ```

---

## 📊 **Repository Statistics**

After setup, your repository will contain:
- **~150 files** across all components
- **~15,000 lines of code** (TypeScript, JavaScript, C++)
- **Complete documentation** with Doxygen formatting
- **Automated CI/CD** with GitHub Actions
- **Production-ready** deployment configurations
- **Comprehensive testing** setup

---

## 🎯 **Next Steps After Repository Creation**

1. **Update README badges** with actual repository URL
2. **Configure branch protection** rules
3. **Set up GitHub Actions** secrets
4. **Create first release** (v1.0.0)
5. **Add contributors** and assign roles
6. **Set up project board** for issue tracking
7. **Configure webhooks** for deployment notifications

---

**Repository URL**: `https://github.com/YOUR_USERNAME/rfid-hotel-management-system`  
**Live Demo**: `https://coastal-grand-tolr.vercel.app`  
**API Endpoint**: `https://coastal-grand-back.onrender.com`  

**Status**: Ready for Production ✅  
**Last Updated**: October 2025