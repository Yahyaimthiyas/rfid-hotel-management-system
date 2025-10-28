#!/bin/bash

/**
 * @file setup.sh
 * @brief Complete project setup script for RFID Hotel Management System
 * @author Development Team
 * @version 1.0.0
 * @date 2024
 */

set -e  # Exit on any error

echo "🏨 RFID Hotel Management System - Setup Script"
echo "=============================================="
echo ""

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Function to print colored output
print_status() {
    echo -e "${GREEN}✅ $1${NC}"
}

print_warning() {
    echo -e "${YELLOW}⚠️  $1${NC}"
}

print_error() {
    echo -e "${RED}❌ $1${NC}"
}

print_info() {
    echo -e "${BLUE}ℹ️  $1${NC}"
}

# Check if Node.js is installed
print_info "Checking Node.js installation..."
if ! command -v node &> /dev/null; then
    print_error "Node.js is not installed. Please install Node.js 18+ first."
    echo "Download from: https://nodejs.org/"
    exit 1
fi

# Check Node.js version
NODE_VERSION=$(node -v | cut -d'v' -f2 | cut -d'.' -f1)
if [ "$NODE_VERSION" -lt 18 ]; then
    print_error "Node.js version 18+ required. Current version: $(node -v)"
    exit 1
fi

print_status "Node.js version: $(node -v)"

# Check if npm is available
if ! command -v npm &> /dev/null; then
    print_error "npm is not available. Please install npm."
    exit 1
fi

print_status "npm version: $(npm -v)"

# Install root dependencies
print_info "Installing root dependencies..."
if [ -f "package.json" ]; then
    npm install
    print_status "Root dependencies installed"
else
    print_warning "No root package.json found, skipping root dependencies"
fi

# Install frontend dependencies
print_info "Installing frontend dependencies..."
if [ -d "Frontend" ] && [ -f "Frontend/package.json" ]; then
    cd Frontend
    npm install
    cd ..
    print_status "Frontend dependencies installed"
elif [ -f "package.json" ]; then
    # If we're in the frontend directory already
    npm install
    print_status "Frontend dependencies installed"
else
    print_warning "No frontend package.json found"
fi

# Install backend dependencies
print_info "Installing backend dependencies..."
if [ -d "Backend" ] && [ -f "Backend/package.json" ]; then
    cd Backend
    npm install
    cd ..
    print_status "Backend dependencies installed"
else
    print_warning "No backend package.json found"
fi

# Create environment files from examples
print_info "Setting up environment files..."

# Frontend environment
if [ ! -f ".env" ] && [ ! -f ".env.local" ]; then
    if [ -f ".env.example" ]; then
        cp .env.example .env.local
        print_status "Created .env.local from example"
    else
        print_warning "No .env.example found. Please create .env.local manually."
    fi
else
    print_status "Frontend environment file already exists"
fi

# Backend environment
if [ ! -f "Backend/.env" ]; then
    if [ -f "Backend/.env.example" ]; then
        cp Backend/.env.example Backend/.env
        print_status "Created Backend/.env from example"
    else
        print_warning "No Backend/.env.example found. Please create Backend/.env manually."
    fi
else
    print_status "Backend environment file already exists"
fi

# Set proper permissions for environment files
print_info "Setting secure permissions for environment files..."
chmod 600 .env* 2>/dev/null || true
chmod 600 Backend/.env* 2>/dev/null || true
print_status "Environment file permissions set"

# Create necessary directories
print_info "Creating necessary directories..."
mkdir -p logs
mkdir -p uploads
mkdir -p scripts
print_status "Directories created"

# Validate environment configuration
print_info "Validating environment configuration..."
if [ -f "scripts/validate-env.js" ]; then
    node scripts/validate-env.js
    if [ $? -eq 0 ]; then
        print_status "Environment validation passed"
    else
        print_warning "Environment validation failed - please check configuration"
    fi
else
    print_warning "Environment validation script not found"
fi

# Check if git is initialized
if [ ! -d ".git" ]; then
    print_info "Initializing git repository..."
    git init
    print_status "Git repository initialized"
fi

# Create .gitignore if it doesn't exist
if [ ! -f ".gitignore" ]; then
    print_info "Creating .gitignore file..."
    cat > .gitignore << 'EOF'
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

# Logs
logs
*.log

# Database
*.db
*.sqlite

# Uploads
uploads/

# OS generated files
.DS_Store
.DS_Store?
._*
Thumbs.db

# Editor directories
.vscode/
.idea/
*.swp
*.swo
EOF
    print_status ".gitignore created"
fi

# Make scripts executable
if [ -d "scripts" ]; then
    chmod +x scripts/*.sh 2>/dev/null || true
    print_status "Scripts made executable"
fi

echo ""
echo "=============================================="
print_status "Setup completed successfully!"
echo "=============================================="
echo ""

print_info "🚀 Next steps:"
echo "1. Update environment variables in .env and Backend/.env"
echo "2. Configure ESP32 settings in 'ESP32 code/config.h'"
echo "3. Run development servers:"
echo "   - Frontend: npm run dev (or cd Frontend && npm run dev)"
echo "   - Backend: cd Backend && npm start"
echo "4. Visit http://localhost:3000 to see the application"
echo ""

print_info "📚 Documentation:"
echo "- README.md - Project overview and demo accounts"
echo "- DEPLOYMENT_GUIDE.md - Production deployment instructions"
echo "- ENVIRONMENT_SETUP.md - Detailed environment configuration"
echo ""

print_info "🔐 Demo Accounts:"
echo "- Admin: admin@hotel.com / admin123"
echo "- Staff: staff@hotel.com / staff123"
echo "- Guest: guest@hotel.com / guest123"
echo ""

print_info "🌐 Live Demo:"
echo "- Frontend: https://coastal-grand-tolr.vercel.app"
echo "- Backend: https://coastal-grand-back.onrender.com"
echo ""

print_status "Happy coding! 🎉"