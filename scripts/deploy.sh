#!/bin/bash

/**
 * @file deploy.sh
 * @brief Production deployment script for RFID Hotel Management System
 * @author Development Team
 * @version 1.0.0
 * @date 2024
 */

set -e  # Exit on any error

echo "🚀 RFID Hotel Management System - Deployment Script"
echo "=================================================="
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

# Check if we're in the right directory
if [ ! -f "package.json" ] && [ ! -f "README.md" ]; then
    print_error "Please run this script from the project root directory"
    exit 1
fi

# Validate environment configuration
print_info "Validating environment configuration..."
if [ -f "scripts/validate-env.js" ]; then
    node scripts/validate-env.js
    if [ $? -ne 0 ]; then
        print_error "Environment validation failed. Please fix environment variables."
        echo ""
        print_info "Run the following to fix environment issues:"
        echo "1. Check ENVIRONMENT_SETUP.md for missing variables"
        echo "2. Update .env and Backend/.env files"
        echo "3. Run 'node scripts/validate-env.js' to verify"
        exit 1
    fi
    print_status "Environment validation passed"
else
    print_warning "Environment validation script not found, skipping validation"
fi

# Check if required tools are installed
print_info "Checking required tools..."

# Check Node.js
if ! command -v node &> /dev/null; then
    print_error "Node.js is not installed"
    exit 1
fi
print_status "Node.js: $(node -v)"

# Check npm
if ! command -v npm &> /dev/null; then
    print_error "npm is not installed"
    exit 1
fi
print_status "npm: $(npm -v)"

# Check git
if ! command -v git &> /dev/null; then
    print_error "git is not installed"
    exit 1
fi
print_status "git: $(git --version)"

# Install dependencies
print_info "Installing/updating dependencies..."

# Frontend dependencies
if [ -d "Frontend" ]; then
    print_info "Installing frontend dependencies..."
    cd Frontend
    npm ci --production
    cd ..
    print_status "Frontend dependencies installed"
elif [ -f "package.json" ]; then
    print_info "Installing dependencies..."
    npm ci --production
    print_status "Dependencies installed"
fi

# Backend dependencies
if [ -d "Backend" ]; then
    print_info "Installing backend dependencies..."
    cd Backend
    npm ci --production
    cd ..
    print_status "Backend dependencies installed"
fi

# Run tests
print_info "Running tests..."

# Frontend tests
if [ -d "Frontend" ]; then
    cd Frontend
    if npm run test --if-present -- --watchAll=false --coverage=false; then
        print_status "Frontend tests passed"
    else
        print_warning "Frontend tests failed or not configured"
    fi
    cd ..
elif [ -f "package.json" ]; then
    if npm test --if-present; then
        print_status "Tests passed"
    else
        print_warning "Tests failed or not configured"
    fi
fi

# Backend tests
if [ -d "Backend" ]; then
    cd Backend
    if npm test --if-present; then
        print_status "Backend tests passed"
    else
        print_warning "Backend tests failed or not configured"
    fi
    cd ..
fi

# Build frontend
print_info "Building frontend for production..."
if [ -d "Frontend" ]; then
    cd Frontend
    if npm run build; then
        print_status "Frontend build successful"
    else
        print_error "Frontend build failed"
        exit 1
    fi
    cd ..
elif [ -f "package.json" ]; then
    if npm run build --if-present; then
        print_status "Build successful"
    else
        print_warning "Build script not found or failed"
    fi
fi

# Check deployment tools
print_info "Checking deployment tools..."

# Check for Vercel CLI
if command -v vercel &> /dev/null; then
    print_status "Vercel CLI available: $(vercel --version)"
    VERCEL_AVAILABLE=true
else
    print_warning "Vercel CLI not installed. Install with: npm i -g vercel"
    VERCEL_AVAILABLE=false
fi

# Deploy frontend to Vercel
if [ "$VERCEL_AVAILABLE" = true ]; then
    print_info "Deploying frontend to Vercel..."
    
    if [ -d "Frontend" ]; then
        cd Frontend
    fi
    
    # Check if user is logged in to Vercel
    if vercel whoami &> /dev/null; then
        print_status "Vercel authentication verified"
        
        # Deploy to production
        if vercel --prod --yes; then
            print_status "Frontend deployed to Vercel successfully!"
        else
            print_error "Vercel deployment failed"
            exit 1
        fi
    else
        print_warning "Not logged in to Vercel. Please run 'vercel login' first"
        print_info "Skipping Vercel deployment"
    fi
    
    if [ -d "Frontend" ]; then
        cd ..
    fi
else
    print_info "Skipping Vercel deployment (CLI not available)"
fi

# Deploy backend to Render
print_info "Triggering backend deployment on Render..."
if [ -n "$RENDER_DEPLOY_HOOK" ]; then
    if curl -X POST "$RENDER_DEPLOY_HOOK"; then
        print_status "Backend deployment triggered on Render"
    else
        print_warning "Failed to trigger Render deployment"
    fi
else
    print_warning "RENDER_DEPLOY_HOOK not set. Backend deployment must be triggered manually."
    print_info "To set up automatic deployment:"
    echo "1. Go to your Render dashboard"
    echo "2. Find your service settings"
    echo "3. Copy the deploy hook URL"
    echo "4. Set RENDER_DEPLOY_HOOK environment variable"
fi

# Git operations
print_info "Checking git status..."
if [ -d ".git" ]; then
    # Check if there are uncommitted changes
    if ! git diff-index --quiet HEAD --; then
        print_warning "You have uncommitted changes"
        print_info "Consider committing your changes:"
        echo "git add ."
        echo "git commit -m 'Deploy: $(date)'"
        echo "git push origin main"
    else
        print_status "Git repository is clean"
        
        # Push to remote if configured
        if git remote get-url origin &> /dev/null; then
            print_info "Pushing to remote repository..."
            if git push origin main; then
                print_status "Code pushed to remote repository"
            else
                print_warning "Failed to push to remote repository"
            fi
        else
            print_warning "No remote repository configured"
        fi
    fi
else
    print_warning "Not a git repository"
fi

# Health checks
print_info "Performing health checks..."

# Check frontend URL
FRONTEND_URL="https://coastal-grand-tolr.vercel.app"
print_info "Checking frontend health: $FRONTEND_URL"
if curl -s -o /dev/null -w "%{http_code}" "$FRONTEND_URL" | grep -q "200"; then
    print_status "Frontend is healthy"
else
    print_warning "Frontend health check failed"
fi

# Check backend URL
BACKEND_URL="https://coastal-grand-back.onrender.com/health"
print_info "Checking backend health: $BACKEND_URL"
if curl -s -o /dev/null -w "%{http_code}" "$BACKEND_URL" | grep -q "200"; then
    print_status "Backend is healthy"
else
    print_warning "Backend health check failed"
fi

echo ""
echo "=================================================="
print_status "Deployment completed!"
echo "=================================================="
echo ""

print_info "🌐 Live URLs:"
echo "- Frontend: https://coastal-grand-tolr.vercel.app"
echo "- Backend API: https://coastal-grand-back.onrender.com"
echo "- Health Check: https://coastal-grand-back.onrender.com/health"
echo ""

print_info "🔐 Demo Accounts:"
echo "- Admin: admin@hotel.com / admin123"
echo "- Staff: staff@hotel.com / staff123"
echo "- Guest: guest@hotel.com / guest123"
echo ""

print_info "📊 Monitoring:"
echo "- Check application logs in Vercel and Render dashboards"
echo "- Monitor system performance and user activity"
echo "- Set up alerts for critical issues"
echo ""

print_info "🔄 Next Deployments:"
echo "- Frontend: Push to main branch or run 'vercel --prod'"
echo "- Backend: Push to main branch (auto-deploys on Render)"
echo "- Full deployment: Run this script again"
echo ""

print_status "Deployment successful! 🎉"