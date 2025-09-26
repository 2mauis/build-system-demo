# CMakePresets User Guide

[![中文](https://img.shields.io/badge/Language-中文-red.svg)](doc/CMakePresets.md) | [English](doc/CMakePresets_EN.md)

## What is CMakePresets?

CMakePresets is a feature introduced in CMake 3.19 and later versions for defining and managing build configuration presets. It allows users to quickly switch between different build environments, generators, and options without manually specifying command-line parameters.

### Advantages
- **Simplified Configuration**: Predefine common settings to avoid repetitive input.
- **Consistency**: Teams can share standard configurations.
- **Flexibility**: Supports inheritance and conditional configurations.
- **Cross-platform**: Works across different operating systems and toolchains.

## File Structure

The CMakePresets.json file contains:
- **version**: Preset format version (version 3 recommended).
- **configurePresets**: Configure presets that define generators, build directories, cache variables, etc.
- **buildPresets**: Build presets that reference configure presets and define build options.
- **testPresets**: Test presets that define CTest options (CMake 3.21+).

## CMakePresets.json in the Project

```json
{
  "version": 3,
  "configurePresets": [
    {
      "name": "default",
      "displayName": "Default Config",
      "description": "Default build using Ninja generator",
      "generator": "Ninja",
      "binaryDir": "${sourceDir}/build",
      "cacheVariables": {
        "CMAKE_CXX_STANDARD": "11",
        "CMAKE_CXX_STANDARD_REQUIRED": "ON"
      }
    },
    {
      "name": "release",
      "displayName": "Release Build",
      "inherits": "default",
      "cacheVariables": {
        "CMAKE_BUILD_TYPE": "Release"
      }
    },
    {
      "name": "debug",
      "displayName": "Debug Build",
      "inherits": "default",
      "cacheVariables": {
        "CMAKE_BUILD_TYPE": "Debug"
      }
    },
    {
      "name": "unix-makefiles",
      "displayName": "Unix Makefiles",
      "description": "Build using Unix Makefiles",
      "generator": "Unix Makefiles",
      "binaryDir": "${sourceDir}/build-make",
      "cacheVariables": {
        "CMAKE_CXX_STANDARD": "11",
        "CMAKE_CXX_STANDARD_REQUIRED": "ON",
        "CMAKE_BUILD_TYPE": "Release"
      }
    }
  ],
  "buildPresets": [
    {
      "name": "default",
      "configurePreset": "default"
    },
    {
      "name": "release",
      "configurePreset": "release"
    },
    {
      "name": "debug",
      "configurePreset": "debug"
    },
    {
      "name": "unix-makefiles",
      "configurePreset": "unix-makefiles"
    }
  ],
  "testPresets": [
    {
      "name": "default",
      "configurePreset": "default",
      "output": {
        "outputOnFailure": true
      }
    },
    {
      "name": "release",
      "configurePreset": "release",
      "output": {
        "outputOnFailure": true
      }
    }
  ]
}
```

### Preset Descriptions
- **configurePresets**: Define build configurations.
- **buildPresets**: Define build options.
- **testPresets**: Define test options, `outputOnFailure` outputs detailed information on failure.

## Usage

### 1. List Presets
```bash
cmake --list-presets
```
Output:
```
Available configure presets:
  "default"        - Default Config
  "release"        - Release Build
  "debug"          - Debug Build
  "unix-makefiles" - Unix Makefiles

Available build presets:
  "default"        -
  "release"        -
  "debug"          -
  "unix-makefiles" -

Available test presets:
  "default"        -
  "release"        -
```

### 2. Configure Project
```bash
cmake --preset <preset-name>
```

### 3. Build Project
```bash
cmake --build --preset <preset-name>
```

### 4. Run Tests
```bash
ctest --preset <preset-name>
```

### 5. Run Executable
```bash
./build/demo  # For Ninja presets
./build-make/demo  # For Unix Makefiles presets
```

## Example Output

### Running Tests
```bash
$ ctest --preset release
No tests were found!!!
```

## Notes
- **testPresets**: Supported, requires the project to have CTest tests (defined in CMakeLists.txt).
- **run**: Does not support directly running executables, needs to be done manually or via scripts.
- Requires CMake 3.21+ for testPresets.
- Preset names are case-sensitive.
- `inherits` allows presets to inherit from others, reducing duplication.
- Build directory is specified by `binaryDir` to avoid polluting the source directory.

## add_test Principle

`add_test` is a CMake command used to define CTest tests.

### Syntax and Parameters
```cmake
add_test(NAME <test_name> COMMAND <executable> [<arg1> <arg2> ...])
```
- **NAME <test_name>**: Unique name for the test.
- **COMMAND <executable>**: Executable or command to run.

### How It Works
1. **Define Tests**: `add_test` registers a test with the CTest system during CMake configuration.
2. **Execution Mechanism**:
   - When `ctest` is run, CTest iterates through all defined tests.
   - For each test, CTest executes the specified command in the build directory.
   - The test process's **exit code** determines the result:
     - **Exit code 0**: Test passes (PASS).
     - **Exit code non-0**: Test fails (FAIL).
3. **Output and Reporting**:
   - CTest collects all test results and displays pass/fail counts.
   - If failures occur, detailed error output can be configured (set `outputOnFailure: true` in testPresets).

### Application in the Project
- **Command**: `add_test(NAME RunDemo COMMAND demo)`
- **Execution**: Runs `./demo` (in the build directory).
- **Check**: If `demo` runs normally and exits (no crashes or errors), exit code is 0, test passes.
- **Result**: `ctest --preset release` outputs test passed.

CMakePresets supports test, but not run.

## Usage

### 1. List Presets
```bash
cmake --list-presets
```
Output:
```
Available configure presets:
  "default"        - Default Config
  "release"        - Release Build
  "debug"          - Debug Build
  "unix-makefiles" - Unix Makefiles

Available build presets:
  "default"        -
  "release"        -
  "debug"          -
  "unix-makefiles" -
```

### 2. Configure Project
```bash
cmake --preset <preset-name>
```
Example:
```bash
cmake --preset release
```

### 3. Build Project
```bash
cmake --build --preset <preset-name>
```
Example:
```bash
cmake --build --preset release
```

### 4. Run Executable
```bash
./build/demo  # For Ninja presets
./build-make/demo  # For Unix Makefiles presets
```

## Example Output

### Configure and Build Release Version
```bash
$ cmake --preset release
-- The C compiler identification is AppleClang 16.0.0.16000026
-- The CXX compiler identification is AppleClang 16.0.0.16000026
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working C compiler: /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc - skipped
-- Detecting C compile features
-- Detecting C compile features - done
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Configuring done (0.5s)
-- Generating done (0.0s)
-- Build files have been written to: /Volumes/DATACS/work/code/samples/class_test/build

$ cmake --build --preset release
[2/4] Building CXX object CMakeFiles/demo.dir/src/main.cpp.o
[3/4] Building CXX object CMakeFiles/demo.dir/src/BaseClass.cpp.o
[4/4] Building CXX object CMakeFiles/demo.dir/src/SubClass.cpp.o
[4/4] Linking CXX executable demo
```

### Run Program
```bash
$ ./build/demo
BaseClass constructor called for SubObject1
SubClass constructor called for SubObject1
BaseClass normal function called by SubObject1
SubClass virtual function overridden by SubObject1
SubClass pure virtual function implemented by SubObject1
BaseClass constructor called for SubObject2
SubClass constructor called for SubObject2
Retrieved object from map
BaseClass normal function called by SubObject1
SubClass virtual function overridden by SubObject1
SubClass pure virtual function implemented by SubObject1
```

## Notes
- Requires CMake 3.19+.
- Preset names are case-sensitive.
- `inherits` allows presets to inherit from others, reducing duplication.
- Build directory is specified by `binaryDir` to avoid polluting the source directory.
- For large projects, more presets can be added, such as cross-compilation or specific toolchains.

CMakePresets simplifies the build process and improves development efficiency.