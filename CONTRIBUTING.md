/**
 * @file CONTRIBUTING.md
 * @brief Contributing Guidelines for RFID Hotel Management System
 * @author Development Team
 * @version 1.0.0
 * @date December 2024
 * 
 * @section overview Contributing Overview
 * 
 * We welcome contributions to the RFID Hotel Management System! This document
 * provides guidelines for contributing to the project, including code standards,
 * development workflow, and submission procedures.
 */

# 🤝 Contributing to RFID Hotel Management System

Thank you for your interest in contributing to the RFID Hotel Management System! This guide will help you get started with contributing to our project.

## 📋 Table of Contents

- [Code of Conduct](#code-of-conduct)
- [Getting Started](#getting-started)
- [Development Workflow](#development-workflow)
- [Code Standards](#code-standards)
- [Commit Guidelines](#commit-guidelines)
- [Pull Request Process](#pull-request-process)
- [Issue Reporting](#issue-reporting)
- [Documentation](#documentation)

---

## 📜 Code of Conduct

### Our Pledge

We are committed to making participation in our project a harassment-free experience for everyone, regardless of age, body size, disability, ethnicity, gender identity and expression, level of experience, nationality, personal appearance, race, religion, or sexual identity and orientation.

### Our Standards

**Positive behavior includes:**
- Using welcoming and inclusive language
- Being respectful of differing viewpoints and experiences
- Gracefully accepting constructive criticism
- Focusing on what is best for the community
- Showing empathy towards other community members

**Unacceptable behavior includes:**
- The use of sexualized language or imagery
- Trolling, insulting/derogatory comments, and personal or political attacks
- Public or private harassment
- Publishing others' private information without explicit permission
- Other conduct which could reasonably be considered inappropriate in a professional setting

---

## 🚀 Getting Started

### Prerequisites

Before contributing, ensure you have:

- **Node.js 18+** installed
- **Git** for version control
- **Code editor** (VS Code recommended)
- **Basic knowledge** of TypeScript, React, and Node.js

### Development Setup

1. **Fork the repository**
   ```bash
   # Fork on GitHub, then clone your fork
   git clone https://github.com/YOUR_USERNAME/rfid-hotel-management-system.git
   cd rfid-hotel-management-system
   ```

2. **Install dependencies**
   ```bash
   # Run the setup script
   npm run setup
   
   # Or manually install
   npm install
   cd Backend && npm install
   ```

3. **Set up environment**
   ```bash
   # Copy environment templates
   cp .env.example .env.local
   cp Backend/.env.example Backend/.env
   
   # Update with your configuration
   ```

4. **Start development servers**
   ```bash
   # Start both frontend and backend
   npm run dev
   
   # Or start individually
   npm run dev:frontend  # Frontend only
   npm run dev:backend   # Backend only
   ```

5. **Validate setup**
   ```bash
   # Run environment validation
   npm run validate-env
   
   # Check system status
   node scripts/status-check.js
   ```

---

## 🔄 Development Workflow

### Branch Strategy

We use **Git Flow** with the following branches:

- **`main`**: Production-ready code
- **`develop`**: Integration branch for features
- **`feature/*`**: New features
- **`bugfix/*`**: Bug fixes
- **`hotfix/*`**: Critical production fixes

### Creating a Feature Branch

```bash
# Create and switch to feature branch
git checkout -b feature/your-feature-name

# Make your changes
# ... code changes ...

# Commit your changes
git add .
git commit -m "feat: add your feature description"

# Push to your fork
git push origin feature/your-feature-name
```

### Keeping Your Fork Updated

```bash
# Add upstream remote (one time setup)
git remote add upstream https://github.com/ORIGINAL_OWNER/rfid-hotel-management-system.git

# Fetch upstream changes
git fetch upstream

# Update your main branch
git checkout main
git merge upstream/main
git push origin main
```

---

## 📝 Code Standards

### TypeScript Standards

```typescript
/**
 * @brief Component description
 * @param props Component properties
 * @returns JSX element
 */
interface ComponentProps {
  /** Property description */
  title: string;
  /** Optional property description */
  subtitle?: string;
}

export function Component({ title, subtitle }: ComponentProps) {
  // Implementation
}
```

### React Component Standards

- **Use functional components** with hooks
- **TypeScript interfaces** for all props
- **JSDoc comments** for documentation
- **Error boundaries** for error handling
- **Accessibility** attributes (ARIA)

### CSS/Styling Standards

- **Tailwind CSS** utility classes
- **Responsive design** with mobile-first approach
- **Dark mode** support
- **Consistent spacing** using design system
- **Performance** optimized styles

### Backend Standards

```javascript
/**
 * @brief API endpoint description
 * @route GET /api/endpoint
 * @param {Object} req Express request object
 * @param {Object} res Express response object
 * @returns {Promise<void>} API response
 */
app.get('/api/endpoint', async (req, res) => {
  try {
    // Implementation
    res.json({ success: true, data: result });
  } catch (error) {
    console.error('Error:', error);
    res.status(500).json({ error: 'Internal server error' });
  }
});
```

### ESP32 Code Standards

```cpp
/**
 * @brief Function description
 * @param parameter Parameter description
 * @return Return value description
 */
bool functionName(int parameter) {
    // Implementation
    return true;
}
```

---

## 📝 Commit Guidelines

### Commit Message Format

We follow the **Conventional Commits** specification:

```
<type>[optional scope]: <description>

[optional body]

[optional footer(s)]
```

### Commit Types

- **`feat`**: New feature
- **`fix`**: Bug fix
- **`docs`**: Documentation changes
- **`style`**: Code style changes (formatting, etc.)
- **`refactor`**: Code refactoring
- **`perf`**: Performance improvements
- **`test`**: Adding or updating tests
- **`chore`**: Maintenance tasks
- **`ci`**: CI/CD changes

### Examples

```bash
# Feature addition
git commit -m "feat(dashboard): add real-time occupancy chart"

# Bug fix
git commit -m "fix(auth): resolve login redirect issue"

# Documentation
git commit -m "docs: update API documentation"

# Refactoring
git commit -m "refactor(components): extract common button logic"
```

---

## 🔍 Pull Request Process

### Before Submitting

1. **Test your changes**
   ```bash
   # Run tests
   npm test
   
   # Validate environment
   npm run validate-env
   
   # Check code quality
   npm run lint
   ```

2. **Update documentation**
   - Update README if needed
   - Add JSDoc comments
   - Update API documentation

3. **Check compatibility**
   - Test on different devices
   - Verify responsive design
   - Test dark/light themes

### Pull Request Template

When creating a pull request, use this template:

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

## Screenshots (if applicable)
Add screenshots to help explain your changes.

## Checklist
- [ ] My code follows the project's style guidelines
- [ ] I have performed a self-review of my own code
- [ ] I have commented my code, particularly in hard-to-understand areas
- [ ] I have made corresponding changes to the documentation
- [ ] My changes generate no new warnings
- [ ] I have added tests that prove my fix is effective or that my feature works
- [ ] New and existing unit tests pass locally with my changes

## Related Issues
Closes #(issue number)
```

### Review Process

1. **Automated checks** must pass
2. **Code review** by maintainers
3. **Testing** on different environments
4. **Documentation** review
5. **Approval** and merge

---

## 🐛 Issue Reporting

### Bug Reports

When reporting bugs, include:

```markdown
**Bug Description**
A clear and concise description of what the bug is.

**Steps to Reproduce**
1. Go to '...'
2. Click on '....'
3. Scroll down to '....'
4. See error

**Expected Behavior**
A clear and concise description of what you expected to happen.

**Screenshots**
If applicable, add screenshots to help explain your problem.

**Environment**
- OS: [e.g. Windows 10, macOS, Ubuntu]
- Browser: [e.g. Chrome, Firefox, Safari]
- Node.js Version: [e.g. 18.17.0]
- Component: [Frontend/Backend/ESP32]

**Additional Context**
Add any other context about the problem here.
```

### Feature Requests

```markdown
**Feature Description**
A clear and concise description of what you want to happen.

**Problem Statement**
A clear and concise description of what the problem is. Ex. I'm always frustrated when [...]

**Proposed Solution**
A clear and concise description of what you want to happen.

**Alternatives Considered**
A clear and concise description of any alternative solutions or features you've considered.

**Additional Context**
Add any other context or screenshots about the feature request here.
```

---

## 📚 Documentation

### Documentation Standards

- **JSDoc comments** for all functions and components
- **README updates** for new features
- **API documentation** for backend changes
- **Code examples** for complex features
- **Deployment guides** for infrastructure changes

### Documentation Types

1. **Code Documentation**
   - Inline comments for complex logic
   - JSDoc for functions and components
   - Type definitions for TypeScript

2. **User Documentation**
   - Feature usage guides
   - Configuration instructions
   - Troubleshooting guides

3. **Developer Documentation**
   - Architecture decisions
   - API specifications
   - Deployment procedures

---

## 🏷️ Component Categories

### Frontend Contributions

- **UI Components**: Reusable interface elements
- **Dashboard Components**: Business logic components
- **Authentication**: Login, signup, and security
- **Analytics**: Charts, metrics, and reporting
- **Real-time Features**: WebSocket and live updates

### Backend Contributions

- **API Endpoints**: RESTful API development
- **Database Models**: MongoDB schema design
- **Real-time Communication**: WebSocket and MQTT
- **Authentication**: JWT and session management
- **Monitoring**: Health checks and logging

### Hardware Contributions

- **ESP32 Code**: RFID integration and IoT features
- **MQTT Communication**: Real-time data transmission
- **Hardware Configuration**: Device setup and management
- **Security**: Access control and encryption

---

## 🎯 Contribution Areas

### High Priority

- **Performance optimization**
- **Mobile responsiveness**
- **Accessibility improvements**
- **Security enhancements**
- **Test coverage**

### Medium Priority

- **New dashboard features**
- **Additional chart types**
- **UI/UX improvements**
- **Documentation updates**
- **Code refactoring**

### Low Priority

- **Code cleanup**
- **Style improvements**
- **Minor bug fixes**
- **Development tools**
- **Build optimizations**

---

## 📞 Getting Help

### Community Support

- **GitHub Discussions**: For questions and general discussion
- **GitHub Issues**: For bug reports and feature requests
- **Documentation**: Comprehensive guides and API docs

### Maintainer Contact

- **Email**: development-team@company.com
- **Response Time**: 24-48 hours for issues
- **Review Time**: 3-5 days for pull requests

---

## 🏆 Recognition

### Contributors

We recognize all contributors in:
- **README.md** contributors section
- **Release notes** for significant contributions
- **GitHub contributors** page
- **Special mentions** for outstanding contributions

### Contribution Types

We value all types of contributions:
- **Code contributions**
- **Documentation improvements**
- **Bug reports**
- **Feature suggestions**
- **Testing and feedback**
- **Community support**

---

Thank you for contributing to the RFID Hotel Management System! Your contributions help make this project better for everyone.

**Happy coding!** 🎉

---

**Last Updated**: December 2024  
**Version**: 1.0.0  
**Maintainers**: Development Team