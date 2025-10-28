/**
 * @file validate-env.js
 * @brief Environment validation script for RFID Hotel Management System
 * @author Development Team
 * @version 1.0.0
 * @date 2024
 */

const fs = require('fs');
const path = require('path');

console.log('🔍 RFID Hotel Management System - Environment Validation\n');

let hasErrors = false;
let hasWarnings = false;

// Frontend environment validation
console.log('📱 Frontend Environment (.env):');
const frontendEnvPath = path.join(__dirname, '..', '.env');
const frontendRequired = [
    'NEXT_PUBLIC_API_URL',
    'NEXT_PUBLIC_SOCKET_URL',
    'NEXTAUTH_SECRET',
    'NEXTAUTH_URL'
];

const frontendOptional = [
    'NEXT_PUBLIC_ENABLE_ANALYTICS',
    'NEXT_PUBLIC_ENABLE_REAL_TIME',
    'NEXT_PUBLIC_DEBUG_MODE'
];

if (fs.existsSync(frontendEnvPath)) {
    const frontendEnv = fs.readFileSync(frontendEnvPath, 'utf8');
    let frontendMissing = [];
    let frontendOptionalMissing = [];
    
    // Check required variables
    frontendRequired.forEach(varName => {
        if (!frontendEnv.includes(varName + '=')) {
            frontendMissing.push(varName);
            hasErrors = true;
        } else {
            const value = frontendEnv.match(new RegExp(`${varName}=(.*)`))?.[1]?.trim();
            if (value && !value.startsWith('your-') && !value.startsWith('CHANGE_')) {
                console.log(`   ✅ ${varName}: ${value.substring(0, 30)}${value.length > 30 ? '...' : ''}`);
            } else {
                console.log(`   ⚠️  ${varName}: Placeholder value detected`);
                hasWarnings = true;
            }
        }
    });
    
    // Check optional variables
    frontendOptional.forEach(varName => {
        if (!frontendEnv.includes(varName + '=')) {
            frontendOptionalMissing.push(varName);
        } else {
            const value = frontendEnv.match(new RegExp(`${varName}=(.*)`))?.[1]?.trim();
            console.log(`   ✅ ${varName}: ${value}`);
        }
    });
    
    if (frontendMissing.length > 0) {
        console.log('   ❌ Missing Required Variables:');
        frontendMissing.forEach(varName => {
            console.log(`      - ${varName}`);
        });
    }
    
    if (frontendOptionalMissing.length > 0) {
        console.log('   ⚠️  Missing Optional Variables:');
        frontendOptionalMissing.forEach(varName => {
            console.log(`      - ${varName}`);
        });
        hasWarnings = true;
    }
} else {
    console.log('   ❌ .env file not found');
    hasErrors = true;
}

// Backend environment validation
console.log('\n🖥️  Backend Environment (Backend/.env):');
const backendEnvPath = path.join(__dirname, '..', 'Backend', '.env');
const backendRequired = [
    'MONGO_URL',
    'PORT',
    'NODE_ENV',
    'JWT_SECRET',
    'SESSION_SECRET',
    'FRONTEND_URL'
];

const backendSecurity = [
    'JWT_SECRET',
    'SESSION_SECRET',
    'ENCRYPTION_KEY',
    'COOKIE_SECRET'
];

if (fs.existsSync(backendEnvPath)) {
    const backendEnv = fs.readFileSync(backendEnvPath, 'utf8');
    let backendMissing = [];
    let weakSecrets = [];
    
    // Check required variables
    backendRequired.forEach(varName => {
        if (!backendEnv.includes(varName + '=')) {
            backendMissing.push(varName);
            hasErrors = true;
        } else {
            const value = backendEnv.match(new RegExp(`${varName}=(.*)`))?.[1]?.trim();
            if (varName.includes('SECRET') || varName.includes('KEY')) {
                console.log(`   ✅ ${varName}: [HIDDEN - ${value?.length || 0} characters]`);
            } else {
                console.log(`   ✅ ${varName}: ${value}`);
            }
        }
    });
    
    // Check security variables strength
    backendSecurity.forEach(varName => {
        const match = backendEnv.match(new RegExp(`${varName}=(.*)`))?.[1]?.trim();
        if (match) {
            if (match.length < 32) {
                weakSecrets.push(`${varName} (${match.length} chars)`);
                hasWarnings = true;
            }
            if (match.startsWith('your-') || match.startsWith('CHANGE_')) {
                weakSecrets.push(`${varName} (placeholder value)`);
                hasErrors = true;
            }
        }
    });
    
    if (backendMissing.length > 0) {
        console.log('   ❌ Missing Required Variables:');
        backendMissing.forEach(varName => {
            console.log(`      - ${varName}`);
        });
    }
    
    if (weakSecrets.length > 0) {
        console.log('   ⚠️  Security Issues:');
        weakSecrets.forEach(issue => {
            console.log(`      - ${issue}`);
        });
    }
} else {
    console.log('   ❌ Backend/.env file not found');
    hasErrors = true;
}

// ESP32 Configuration Check
console.log('\n🔌 ESP32 Configuration (ESP32 code/config.h):');
const esp32ConfigPath = path.join(__dirname, '..', 'ESP32 code', 'config.h');

if (fs.existsSync(esp32ConfigPath)) {
    const esp32Config = fs.readFileSync(esp32ConfigPath, 'utf8');
    
    // Check for placeholder values
    const placeholders = [
        'YOUR_WIFI_NETWORK_NAME',
        'YOUR_WIFI_PASSWORD',
        'CHANGE_THIS'
    ];
    
    let hasPlaceholders = false;
    placeholders.forEach(placeholder => {
        if (esp32Config.includes(placeholder)) {
            hasPlaceholders = true;
        }
    });
    
    if (hasPlaceholders) {
        console.log('   ⚠️  ESP32 config contains placeholder values');
        console.log('      - Update WiFi credentials');
        console.log('      - Configure room-specific parameters');
        hasWarnings = true;
    } else {
        console.log('   ✅ ESP32 configuration appears to be customized');
    }
    
    // Check for room configuration
    if (esp32Config.includes('#define ROOM_NUMBER "202"')) {
        console.log('   ✅ Room number configured: 202');
    }
    if (esp32Config.includes('#define FLOOR_NUMBER "3"')) {
        console.log('   ✅ Hotel ID configured: 3 (Yercaud)');
    }
} else {
    console.log('   ❌ ESP32 config.h file not found');
    hasErrors = true;
}

// Summary
console.log('\n' + '='.repeat(60));
console.log('📊 VALIDATION SUMMARY');
console.log('='.repeat(60));

if (!hasErrors && !hasWarnings) {
    console.log('✅ All environment configurations are valid!');
    console.log('🚀 System is ready for deployment.');
} else if (!hasErrors && hasWarnings) {
    console.log('⚠️  Environment validation passed with warnings.');
    console.log('💡 Consider addressing warnings for optimal security.');
} else {
    console.log('❌ Environment validation failed!');
    console.log('🔧 Please fix the errors above before deployment.');
}

console.log('\n📚 For detailed setup instructions, see:');
console.log('   - ENVIRONMENT_SETUP.md');
console.log('   - DEPLOYMENT_GUIDE.md');

// Exit with appropriate code
process.exit(hasErrors ? 1 : 0);