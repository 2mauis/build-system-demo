# CI/CD Guide

[![中文](https://img.shields.io/badge/Language-中文-red.svg)](doc/CI.md) | [English](doc/CI_EN.md)

This project is configured with GitHub Actions, supporting manual triggering of compilation in three build methods.

## Supported Workflows

### CMakePresets Workflow

- **File**: `.github/workflows/cmake-presets.yml`
- **Trigger**: Manual trigger (workflow_dispatch)
- **Supported Presets**: default, release, debug
- **Function**: Configure builds and tests using CMakePresets

### Bazel Workflow

- **File**: `.github/workflows/bazel.yml`
- **Trigger**: Manual trigger (workflow_dispatch)
- **Function**: Build and test directly using Bazel

### Bazelisk Workflow

- **File**: `.github/workflows/bazelisk.yml`
- **Trigger**: Manual trigger (workflow_dispatch)
- **Function**: Automatically manage Bazel versions and build tests using Bazelisk

### Clang-Tidy Workflow

- **File**: `.github/workflows/clang-tidy.yml`
- **Trigger**: Manual trigger (workflow_dispatch)
- **Function**: Perform static code analysis and quality checks using Clang-Tidy

### Coverity SCA Workflow

- **File**: `.github/workflows/coverity.yml`
- **Trigger**: Manual trigger (workflow_dispatch)
- **Function**: Perform static code analysis and security checks using Coverity
- **Requirements**: Configure COVERITY_TOKEN and COVERITY_EMAIL secrets

## How to Use

1. Go to the Actions tab of the GitHub repository
2. Select the desired workflow
3. Click the "Run workflow" button
4. Adjust input parameters as needed
5. Click "Run workflow" to start building

## Workflow Configuration Details

### CMakePresets Configuration

This workflow uses CMake's preset functionality, supporting different build configurations:

- **default**: Default configuration
- **release**: Release version optimization configuration
- **debug**: Debug version configuration

### Bazel Configuration

Directly use Bazel for building, supporting custom targets:

- **target**: Bazel target to build (default: `//:demo`)
- **test_target**: Test target to run (optional, default: empty, no tests run)

### Bazelisk Configuration

Use Bazelisk for building, automatically managing Bazel versions:

- **target**: Bazel target to build (default: `//:demo`)
- **test_target**: Test target to run (optional, default: empty, no tests run)

### Clang-Tidy Configuration

Use Clang-Tidy for static code analysis:

- **build_type**: Build type (Debug/Release, default: Debug)
- **Function**: Generate compilation database and run clang-tidy analysis on all source files

### Coverity Configuration

Use Coverity for static code analysis:

- **build_type**: Build type (Debug/Release, default: Debug)
- **Function**: Run Coverity analysis and upload results to Coverity server
- **Requirements**: Configure COVERITY_TOKEN and COVERITY_EMAIL in GitHub secrets

## Environment Requirements

All workflows run on the latest Ubuntu version, automatically installing required dependencies:

- CMake workflow: Install cmake and ninja-build
- Bazel workflow: Install Bazel from official repository
- Bazelisk workflow: Download and install Bazelisk
- Clang-Tidy workflow: Install cmake, ninja-build, and clang-tidy
- Coverity workflow: Install cmake, ninja-build, and download Coverity tools

## GitHub Secrets Configuration

For the Coverity workflow, configure the following secrets in the repository settings:

- `COVERITY_TOKEN`: Coverity scan token
- `COVERITY_EMAIL`: Email address associated with Coverity account

## Troubleshooting

If workflows fail, please check:

1. Code syntax errors
2. Missing dependencies
3. Build configuration issues
4. Network connection issues (when downloading dependencies)

### Clang-Tidy Specific Issues
- Ensure all header file paths are correct
- Check clang-tidy configuration and warning levels

### Coverity Specific Issues
- Confirm COVERITY_TOKEN and COVERITY_EMAIL are configured correctly
- Check Coverity account permissions
- Confirm the project is registered in Coverity

You can view detailed logs in the Actions tab.