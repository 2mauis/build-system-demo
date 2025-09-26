# Bazel Usage and Principles

[![中文](https://img.shields.io/badge/Language-中文-red.svg)](Bazel.md) | [English](Bazel_EN.md)

## What is Bazel?

Bazel is an open-source build and test tool developed by Google. It supports multi-language projects (C++, Java, Python, etc.), emphasizing scalability, performance, and correctness. Bazel is suitable for large codebases and can handle complex dependencies and parallel builds.

### Core Features
- **Incremental Builds**: Only rebuilds changed parts.
- **Distributed Builds**: Supports remote execution and caching.
- **Multi-language Support**: Built-in rules support multiple programming languages.
- **Extensible**: Extend functionality through custom rules.
- **Sandboxed**: Builds run in isolated environments, ensuring reproducibility.

## Bazel Principles

### Build Graph
- Bazel models projects as directed acyclic graphs (DAGs), where nodes are targets and edges are dependencies.
- Targets include libraries (cc_library), binaries (cc_binary), etc.
- Bazel analyzes dependencies to determine build order.

### Incremental Builds
- Uses content hashing to detect file changes.
- Only rebuilds affected targets.
- Caches build artifacts to avoid redundant work.

### Module System (Bzlmod)
- Introduced in Bazel 8.x for managing external dependencies.
- Enabled by default, but can be disabled to use WORKSPACE mode.
- Modules are defined in MODULE.bazel files.

### WORKSPACE Mode
- Traditional approach using WORKSPACE files to define external dependencies.
- Downloads dependencies through rules like http_archive.
- Will be removed in Bazel 9, migration to Bzlmod is recommended.

### Toolchains and Platforms
- Bazel uses toolchains to abstract compilers, linkers, etc.
- Platforms define target environments (OS, architecture).
- Automatically selects appropriate toolchains.

## Usage in Projects

### Project Structure
```
class_test/
├── WORKSPACE          # Defines workspace
├── BUILD              # Defines build targets
├── .bazelrc           # Bazel configuration
├── MODULE.bazel       # Module definitions (Bzlmod)
├── src/               # Source code
└── include/           # Header files
```

### WORKSPACE File
```starlark
workspace(name = "class_test")
```

### BUILD File
```starlark
cc_library(
    name = "base_class",
    hdrs = ["include/BaseClass.h"],
    srcs = ["src/BaseClass.cpp"],
    strip_include_prefix = "include",
    visibility = ["//visibility:public"],
)

cc_library(
    name = "sub_class",
    hdrs = ["include/SubClass.h"],
    srcs = ["src/SubClass.cpp"],
    strip_include_prefix = "include",
    deps = [":base_class"],
    visibility = ["//visibility:public"],
)

cc_binary(
    name = "demo",
    srcs = ["src/main.cpp"],
    deps = [":sub_class"],
)
```

### MODULE.bazel File
```starlark
module(
    name = "class_test",
    version = "1.0.0",
    bazel = "8.4.1",
)
```

### .bazelrc File
```bash
# Enable Bzlmod
common --enable_bzlmod=true
common --enable_workspace=true

# Build settings
common --compilation_mode=fastbuild
```

## Build Commands

### Basic Commands
```bash
# Build target
bazel build //:demo

# Run target
bazel run //:demo

# Test (if tests exist)
bazel test //:demo_test

# Clean build artifacts
bazel clean

# Query dependencies
bazel query 'deps(//:demo)'
```

### Advanced Usage
```bash
# Build with specific configuration
bazel build --compilation_mode=opt //:demo

# Build multiple targets
bazel build //:demo //:other_target

# Show build graph
bazel query 'deps(//:demo)' --output graph

# Analyze build performance
bazel build --profile=/tmp/profile.gz //:demo
bazel analyze-profile /tmp/profile.gz
```

## Configuration Files

### .bazelrc
Bazel configuration file, can set default options:
```bash
# Common settings
common --compilation_mode=fastbuild
common --strip=never

# C++ specific
build --cxxopt=-std=c++11
build --cxxopt=-Wall

# Test settings
test --test_output=errors
test --test_timeout=60
```

### MODULE.bazel
For Bzlmod dependency management:
```starlark
module(
    name = "class_test",
    version = "1.0.0",
    bazel = "8.4.1",
)

bazel_dep(name = "rules_cc", version = "0.0.9")
```

## Best Practices

### Project Organization
- Use clear package structure
- Define appropriate visibility
- Use consistent naming conventions

### Build Optimization
- Minimize dependencies
- Use appropriate compilation modes
- Leverage caching and remote execution

### Dependency Management
- Prefer Bzlmod over WORKSPACE
- Keep dependencies up to date
- Use version ranges carefully

## Troubleshooting

### Common Issues
- **Missing dependencies**: Check MODULE.bazel or WORKSPACE
- **Toolchain issues**: Verify platform and toolchain configuration
- **Cache problems**: Try `bazel clean --expunge`

### Debug Commands
```bash
# Show detailed build output
bazel build -s //:demo

# Show dependency graph
bazel query 'deps(//:demo)' --output graph

# Analyze build performance
bazel build --profile=build.profile //:demo
```

## Integration with CI/CD

Bazel works well with CI/CD systems:

- **Caching**: Build artifacts can be cached between runs
- **Parallel execution**: Supports distributed builds
- **Test integration**: Native test support
- **Artifact management**: Easy to package and deploy

## Resources

- [Official Bazel Documentation](https://bazel.build)
- [Bazel Rules](https://bazel.build/reference/be)
- [Bzlmod Guide](https://bazel.build/external/overview)