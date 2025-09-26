# Bazelisk User Guide

[![中文](https://img.shields.io/badge/Language-中文-red.svg)](Bazelisk.md) | [English](Bazelisk_EN.md)

## What is Bazelisk?

Bazelisk is an open-source tool for automatically managing and running the correct Bazel version. It is a version manager for Bazel, similar to version managers for other languages (like nvm for Node.js or rbenv for Ruby).

### Core Features

- **Automatic Version Selection**: Automatically downloads and uses the appropriate Bazel version based on project configuration.
- **Seamless Integration**: Fully compatible with standard Bazel commands, no need to modify existing scripts.
- **Team Consistency**: Ensures all developers use the same Bazel version, avoiding version conflicts.
- **CI/CD Friendly**: Automatically handles version management in continuous integration environments.

### Difference from Bazel

- **Bazel**: Direct build tool that requires manual installation of specific versions.
- **Bazelisk**: Version manager that automatically handles Bazel version selection and installation.

## Installation Steps

### macOS (using Homebrew)

```bash
# If Bazel is already installed, unlink it first
brew unlink bazel

# Install Bazelisk
brew install bazelisk

# Verify installation
bazelisk version
```

### Linux

```bash
# Download the latest version
curl -L https://github.com/bazelbuild/bazelisk/releases/latest/download/bazelisk-linux-amd64 -o bazelisk
chmod +x bazelisk

# Move to PATH
sudo mv bazelisk /usr/local/bin/

# Verify installation
bazelisk version
```

### Windows

```powershell
# Using Chocolatey
choco install bazelisk

# Or download binary
# https://github.com/bazelbuild/bazelisk/releases
```

## Usage Steps

### Basic Commands

Bazelisk commands are identical to Bazel:

```bash
# Build target
bazelisk build //:target

# Run target
bazelisk run //:target

# Test
bazelisk test //:target

# Clean
bazelisk clean

# Query
bazelisk query 'deps(//:target)'

# Show version
bazelisk version
```

### Version Selection Mechanism

Bazelisk selects Bazel versions in the following priority order:

1. **.bazelversion file**: File in project root specifying version.

   ```text
   8.4.1
   ```

2. **WORKSPACE.bazelrc or .bazelrc**: USE_BAZEL_VERSION in configuration.

   ```text
   common --repo_env=USE_BAZEL_VERSION=8.4.1
   ```

3. **MODULE.bazel**: bazel field in Bzlmod.

   ```starlark
   bazel = "8.4.1"
   ```

4. **Automatic Selection**: Uses latest stable version if not specified.

### Project Configuration Examples

#### .bazelversion file

Create `.bazelversion` in project root:

```text
8.4.1
```

#### .bazelrc configuration

```bash
# Specify Bazel version
common --repo_env=USE_BAZEL_VERSION=8.4.1

# Other configurations
common --enable_bzlmod=true
common --enable_workspace=true
```

## Usage in Projects

### Example Project Structure

```text
my_project/
├── .bazelversion    # Specify Bazel version
├── .bazelrc         # Bazel configuration
├── WORKSPACE        # Workspace definition
├── BUILD            # Build rules
└── src/             # Source code
```

### Build Workflow

```bash
# Enter project directory
cd my_project

# Build (automatically downloads appropriate Bazel version)
bazelisk build //:demo

# Run
bazelisk run //:demo

# Test
bazelisk test //:demo_test
```

### CI/CD Integration

Using in GitHub Actions:

```yaml
- name: Setup Bazelisk
  run: |
    curl -L https://github.com/bazelbuild/bazelisk/releases/latest/download/bazelisk-linux-amd64 -o bazelisk
    chmod +x bazelisk
    sudo mv bazelisk /usr/local/bin/

- name: Build
  run: bazelisk build //:target
```

## Advantages and Best Practices

### Advantages

- **Version Consistency**: Team members automatically use the same Bazel version.
- **Simplified Installation**: No need to manually manage Bazel versions.
- **Backward Compatibility**: Existing Bazel scripts don't need modification.
- **Easy Updates**: Can easily upgrade to new versions.

### Best Practices

- **Fixed Versions**: Specify exact versions in `.bazelversion` to ensure reproducible builds.
- **Regular Updates**: Regularly update Bazel versions to get latest features and fixes.
- **Documentation**: Document the Bazel version used in project README.
- **CI Configuration**: Specify versions explicitly in CI to avoid unexpected upgrades.

## Troubleshooting

### Common Issues

- **Version Mismatch**: Check `.bazelversion` file.
- **Download Failure**: Check network connection, retry command.
- **Permission Issues**: Ensure permissions to download and install Bazel.

### Getting Help

- [Bazelisk GitHub](https://github.com/bazelbuild/bazelisk)
- [Bazel Documentation](https://bazel.build)

Bazelisk simplifies Bazel version management, making the build process more reliable and consistent.