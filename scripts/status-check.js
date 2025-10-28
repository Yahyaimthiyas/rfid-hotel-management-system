/**
 * @file status-check.js
 * @brief System status check script for RFID Hotel Management System
 * @author Development Team
 * @version 1.0.0
 * @date 2024
 */

const https = require('https');
const http = require('http');
const fs = require('fs');
const path = require('path');

console.log('🏨 RFID Hotel Management System - Status Check');
console.log('='.repeat(50));
console.log('');

// Configuration
const config = {
    frontend: {
        url: 'https://coastal-grand-tolr.vercel.app',
        name: 'Frontend (Vercel)'
    },
    backend: {
        url: 'https://coastal-grand-back.onrender.com',
        healthEndpoint: '/health',
        name: 'Backend (Render)'
    },
    api: {
        url: 'https://coastal-grand-back.onrender.com/api',
        endpoints: ['/hotels', '/health/env'],
        name: 'API Endpoints'
    }
};

// Colors for console output
const colors = {
    green: '\x1b[32m',
    red: '\x1b[31m',
    yellow: '\x1b[33m',
    blue: '\x1b[34m',
    reset: '\x1b[0m'
};

// Helper functions
const success = (msg) => console.log(`${colors.green}✅ ${msg}${colors.reset}`);
const error = (msg) => console.log(`${colors.red}❌ ${msg}${colors.reset}`);
const warning = (msg) => console.log(`${colors.yellow}⚠️  ${msg}${colors.reset}`);
const info = (msg) => console.log(`${colors.blue}ℹ️  ${msg}${colors.reset}`);

// HTTP request helper
function makeRequest(url, timeout = 10000) {
    return new Promise((resolve, reject) => {
        const client = url.startsWith('https') ? https : http;
        const startTime = Date.now();
        
        const req = client.get(url, (res) => {
            const responseTime = Date.now() - startTime;
            let data = '';
            
            res.on('data', (chunk) => {
                data += chunk;
            });
            
            res.on('end', () => {
                resolve({
                    statusCode: res.statusCode,
                    responseTime,
                    data,
                    headers: res.headers
                });
            });
        });
        
        req.on('error', (err) => {
            reject({
                error: err.message,
                responseTime: Date.now() - startTime
            });
        });
        
        req.setTimeout(timeout, () => {
            req.destroy();
            reject({
                error: 'Request timeout',
                responseTime: timeout
            });
        });
    });
}

// Check service status
async function checkService(name, url, expectedStatus = 200) {
    info(`Checking ${name}...`);
    
    try {
        const result = await makeRequest(url);
        
        if (result.statusCode === expectedStatus) {
            success(`${name}: Online (${result.responseTime}ms)`);
            return { status: 'online', responseTime: result.responseTime, data: result.data };
        } else {
            warning(`${name}: Unexpected status ${result.statusCode} (${result.responseTime}ms)`);
            return { status: 'warning', responseTime: result.responseTime, statusCode: result.statusCode };
        }
    } catch (err) {
        error(`${name}: ${err.error} (${err.responseTime}ms)`);
        return { status: 'offline', error: err.error, responseTime: err.responseTime };
    }
}

// Check environment files
function checkEnvironmentFiles() {
    info('Checking environment configuration...');
    
    const envFiles = [
        { path: '.env', name: 'Frontend Environment' },
        { path: 'Backend/.env', name: 'Backend Environment' },
        { path: '.env.example', name: 'Frontend Example' },
        { path: 'Backend/.env.example', name: 'Backend Example' }
    ];
    
    let allGood = true;
    
    envFiles.forEach(file => {
        const fullPath = path.join(__dirname, '..', file.path);
        if (fs.existsSync(fullPath)) {
            success(`${file.name}: Found`);
        } else {
            error(`${file.name}: Missing (${file.path})`);
            allGood = false;
        }
    });
    
    return allGood;
}

// Check project structure
function checkProjectStructure() {
    info('Checking project structure...');
    
    const requiredDirs = [
        'Backend',
        'ESP32 code',
        'components',
        'app',
        'lib',
        'hooks',
        'scripts'
    ];
    
    const requiredFiles = [
        'README.md',
        'package.json',
        'DEPLOYMENT_GUIDE.md',
        'ENVIRONMENT_SETUP.md'
    ];
    
    let allGood = true;
    
    // Check directories
    requiredDirs.forEach(dir => {
        const dirPath = path.join(__dirname, '..', dir);
        if (fs.existsSync(dirPath)) {
            success(`Directory: ${dir}`);
        } else {
            warning(`Directory missing: ${dir}`);
        }
    });
    
    // Check files
    requiredFiles.forEach(file => {
        const filePath = path.join(__dirname, '..', file);
        if (fs.existsSync(filePath)) {
            success(`File: ${file}`);
        } else {
            error(`File missing: ${file}`);
            allGood = false;
        }
    });
    
    return allGood;
}

// Main status check function
async function runStatusCheck() {
    console.log('🔍 Starting comprehensive status check...\n');
    
    const results = {
        services: {},
        environment: false,
        structure: false,
        overall: 'unknown'
    };
    
    // Check project structure
    console.log('📁 Project Structure:');
    results.structure = checkProjectStructure();
    console.log('');
    
    // Check environment files
    console.log('🔧 Environment Configuration:');
    results.environment = checkEnvironmentFiles();
    console.log('');
    
    // Check services
    console.log('🌐 Service Status:');
    
    // Frontend check
    results.services.frontend = await checkService(
        config.frontend.name,
        config.frontend.url
    );
    
    // Backend health check
    results.services.backend = await checkService(
        config.backend.name,
        config.backend.url + config.backend.healthEndpoint
    );
    
    // API endpoints check
    for (const endpoint of config.api.endpoints) {
        const endpointName = `API ${endpoint}`;
        results.services[`api_${endpoint.replace('/', '_')}`] = await checkService(
            endpointName,
            config.api.url + endpoint
        );
    }
    
    console.log('');
    
    // Overall status
    const serviceStatuses = Object.values(results.services);
    const onlineServices = serviceStatuses.filter(s => s.status === 'online').length;
    const totalServices = serviceStatuses.length;
    
    if (onlineServices === totalServices && results.environment && results.structure) {
        results.overall = 'healthy';
        success('Overall Status: All systems operational! 🎉');
    } else if (onlineServices > totalServices / 2) {
        results.overall = 'degraded';
        warning('Overall Status: Some issues detected ⚠️');
    } else {
        results.overall = 'unhealthy';
        error('Overall Status: Multiple issues detected 🚨');
    }
    
    // Summary
    console.log('\n' + '='.repeat(50));
    console.log('📊 STATUS SUMMARY');
    console.log('='.repeat(50));
    
    console.log(`Services Online: ${onlineServices}/${totalServices}`);
    console.log(`Environment: ${results.environment ? 'OK' : 'Issues'}`);
    console.log(`Structure: ${results.structure ? 'OK' : 'Issues'}`);
    
    // Service details
    console.log('\n🌐 Service Details:');
    Object.entries(results.services).forEach(([key, service]) => {
        const status = service.status === 'online' ? '✅' : 
                      service.status === 'warning' ? '⚠️' : '❌';
        console.log(`   ${status} ${key}: ${service.status} (${service.responseTime}ms)`);
    });
    
    // Recommendations
    if (results.overall !== 'healthy') {
        console.log('\n💡 Recommendations:');
        
        if (!results.environment) {
            console.log('   - Fix environment configuration (see ENVIRONMENT_SETUP.md)');
        }
        
        if (!results.structure) {
            console.log('   - Ensure all required files and directories are present');
        }
        
        const offlineServices = serviceStatuses.filter(s => s.status === 'offline');
        if (offlineServices.length > 0) {
            console.log('   - Check offline services and deployment status');
        }
    }
    
    // Demo information
    console.log('\n🔐 Demo Accounts:');
    console.log('   - Admin: admin@hotel.com / admin123');
    console.log('   - Staff: staff@hotel.com / staff123');
    console.log('   - Guest: guest@hotel.com / guest123');
    
    console.log('\n🌐 Live URLs:');
    console.log(`   - Frontend: ${config.frontend.url}`);
    console.log(`   - Backend: ${config.backend.url}`);
    console.log(`   - API: ${config.api.url}`);
    
    console.log('\n📚 Documentation:');
    console.log('   - README.md - Project overview');
    console.log('   - DEPLOYMENT_GUIDE.md - Deployment instructions');
    console.log('   - ENVIRONMENT_SETUP.md - Environment configuration');
    
    return results;
}

// Run the status check
if (require.main === module) {
    runStatusCheck()
        .then(results => {
            process.exit(results.overall === 'healthy' ? 0 : 1);
        })
        .catch(err => {
            error(`Status check failed: ${err.message}`);
            process.exit(1);
        });
}

module.exports = { runStatusCheck, checkService };