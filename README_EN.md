# C++ Class Inheritance Demo: Pure Virtual, Virtual, and Normal Functions (CMake/Bazel Build System Demo)

> **This project is built and tested using Copilot Agent mode** - The entire project (including code, build systems, CI/CD, documentation) is automatically generated and configured by the Grok Code Fast (Preview) model.

[![中文](https://img.shields.io/badge/Language-中文-red.svg)](README.md) | [English](README_EN.md)

This project demonstrates the concept of class inheritance in C++, including the usage and differences between pure virtual functions, virtual functions, and normal functions. Through concrete code examples, it shows how these functions behave in class hierarchies. At the same time, it demonstrates the complete build system configuration for modern C++ projects, including multiple build tools such as CMake, CMakePresets, Bazel, and Bazelisk.

## Project Structure

- `BaseClass`: Base class containing pure virtual functions, virtual functions, and normal functions.
- `SubClass`: Derived class inheriting from `BaseClass`, implementing pure virtual functions and overriding virtual functions.
- `main.cpp`: Main function that creates objects and calls functions to demonstrate polymorphism.

## Build Systems

This project supports multiple build systems:

### Using CMake
- Install CMake 3.19+.
- Build: `cmake --preset default && cmake --build --preset default`
- Run: `./build/demo`

Detailed information: [CMakePresets.md](doc/CMakePresets_EN.md)

### Using Bazel
- Install Bazel or [Bazelisk](doc/Bazelisk_EN.md) (recommended).
- Build: `bazel build //:demo`
- Run: `bazel run //:demo`

Detailed information: [Bazel.md](doc/Bazel_EN.md) and [Bazelisk.md](doc/Bazelisk_EN.md)

## Function Types Explanation

### 1. Normal Functions

#### Definition
Normal functions are regular member functions without any special keywords.

#### Usage
- Defined in the base class with function body.
- Can be inherited by derived classes.
- Can be overridden in derived classes (hides base class version).

#### Differences
- No polymorphism: Call depends on pointer type, not actual object type.

#### Example
In `BaseClass`:
```cpp
void normalFunction() {
    std::cout << "BaseClass normal function" << std::endl;
}
```
In `SubClass` override:
```cpp
void normalFunction() {
    std::cout << "SubClass normal function overridden" << std::endl;
}
```
In `main.cpp` call:
```cpp
sub->normalFunction();  // Output: SubClass normal function overridden
```

### 2. Virtual Functions

#### Definition
Virtual functions are declared with the `virtual` keyword and can provide a default implementation.

#### Usage
- Declared as `virtual` in base class, can provide default implementation.
- Derived classes can override them optionally.

#### Differences
- Supports polymorphism: Call depends on actual object type.

#### Example
In `BaseClass`:
```cpp
virtual void virtualFunction() {
    std::cout << "BaseClass virtual function" << std::endl;
}
```
In `SubClass` override:
```cpp
void virtualFunction() override {
    std::cout << "SubClass virtual function overridden by " << name << std::endl;
}
```
In `main.cpp` call:
```cpp
sub->virtualFunction();  // Output: SubClass virtual function overridden by SubObject1
```
When called through `BaseClass` pointer, it also executes `SubClass` version.

### 3. Pure Virtual Functions

#### Definition
Pure virtual functions are declared as `virtual` and end with `= 0`, with no implementation. Makes the class abstract and cannot be instantiated.

#### Usage
- Declared in base class: `virtual void func() = 0;`
- Derived classes must provide implementation, otherwise cannot instantiate.

## CI/CD

Detailed CI/CD configuration and usage instructions: [CI.md](doc/CI_EN.md)

## Changelog

### Recent Commits

- `c9075d5` Update changelog with AI model specification
- `4ceed06` Update AI development note to specify Copilot Agent mode with Grok Code Fast model
- `f9246dc` Update changelog with license addition
- `d73cb36` Add BSD-3-Clause license and note about agentic AI development
- `ea4d704` Final changelog update with clang-tidy config
- `7422cfa` Add .clang-tidy config file and update workflow to use it
- `6d53654` Update changelog with new static analysis workflows
- `62fa561` Add Clang-Tidy and Coverity SCA workflows and update CI documentation
- `21c47a0` Final changelog update
- `a891870` Update CI documentation to reflect test target changes
- `04a2726` Update changelog with workflow fix
- `a6532f9` Fix Bazel workflows: remove default test target that doesn't exist
- `c3ba48f` Update changelog with latest commit
- `4e5423e` Extract CI/CD documentation to separate CI.md file and update README reference
- `bb34efd` Add CI/CD section to README documenting GitHub Actions workflows
- `7a7ae49` Add GitHub Actions workflows for CMakePresets, Bazel, and Bazelisk builds
- `3b9acaa` Update README with latest commit record
- `5960f71` Add Bazelisk documentation and update README with Bazelisk link
- `e2a25cb` Add CMakePresets, CTest integration, and documentation updates
- `49744ee` Initial commit: C++ class inheritance demo with CMake and Bazel build support