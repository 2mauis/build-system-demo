# CMakePresets 使用指南

## 什么是CMakePresets？

CMakePresets是CMake 3.19及以上版本引入的功能，用于定义和管理构建配置的预设。它允许用户快速切换不同的构建环境、生成器和选项，而无需手动指定命令行参数。

### 优势
- **简化配置**：预定义常用设置，避免重复输入。
- **一致性**：团队共享标准配置。
- **灵活性**：支持继承和条件配置。
- **跨平台**：适用于不同操作系统和工具链。

## 文件结构

CMakePresets.json 文件包含：
- **version**: 预设格式版本（推荐3）。
- **configurePresets**: 配置预设，定义生成器、构建目录、缓存变量等。
- **buildPresets**: 构建预设，引用配置预设并定义构建选项。
- **testPresets**: 测试预设，定义CTest选项（CMake 3.21+）。

## 项目中的CMakePresets.json

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

### 预设说明
- **configurePresets**: 定义构建配置。
- **buildPresets**: 定义构建选项。
- **testPresets**: 定义测试选项，`outputOnFailure`在失败时输出详细信息。

## 使用方法

### 1. 列出预设
```bash
cmake --list-presets
```
输出：
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

### 2. 配置项目
```bash
cmake --preset <preset-name>
```

### 3. 构建项目
```bash
cmake --build --preset <preset-name>
```

### 4. 运行测试
```bash
ctest --preset <preset-name>
```

### 5. 运行可执行文件
```bash
./build/demo  # 对于Ninja预设
./build-make/demo  # 对于Unix Makefiles预设
```

## 示例输出

### 运行测试
```bash
$ ctest --preset release
No tests were found!!!
```

## 注意事项
- **testPresets**: 支持，需要项目有CTest测试（在CMakeLists.txt中定义）。
- **run**: 不支持直接运行可执行文件，需手动或脚本实现。
- 需要CMake 3.21+ for testPresets。
- 预设名称区分大小写。
- `inherits`允许预设继承，减少重复。
- 构建目录由`binaryDir`指定，避免污染源目录。

## add_test 原理

`add_test` 是CMake中的命令，用于定义CTest测试。

### 语法和参数
```cmake
add_test(NAME <test_name> COMMAND <executable> [<arg1> <arg2> ...])
```
- **NAME <test_name>**: 测试的唯一名称。
- **COMMAND <executable>**: 要运行的可执行文件或命令。

### 工作原理
1. **定义测试**：`add_test` 在CMake配置时注册一个测试到CTest系统中。
2. **执行机制**：
   - 当运行 `ctest` 时，CTest会遍历所有定义的测试。
   - 对于每个测试，CTest在构建目录中执行指定的命令。
   - 测试进程的**退出码**决定结果：
     - **退出码 0**：测试通过（PASS）。
     - **退出码非0**：测试失败（FAIL）。
3. **输出和报告**：
   - CTest收集所有测试结果，显示通过/失败数量。
   - 如果失败，可配置输出详细错误信息（在testPresets中设置 `outputOnFailure: true`）。

### 在项目中的应用
- **命令**：`add_test(NAME RunDemo COMMAND demo)`
- **执行**：运行 `./demo`（在build目录中）。
- **检查**：如果 `demo` 正常运行并退出（无崩溃或错误），退出码为0，测试通过。
- **结果**：`ctest --preset release` 输出测试通过。

CMakePresets支持test，但不支持run。

## 使用方法

### 1. 列出预设
```bash
cmake --list-presets
```
输出：
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

### 2. 配置项目
```bash
cmake --preset <preset-name>
```
例如：
```bash
cmake --preset release
```

### 3. 构建项目
```bash
cmake --build --preset <preset-name>
```
例如：
```bash
cmake --build --preset release
```

### 4. 运行可执行文件
```bash
./build/demo  # 对于Ninja预设
./build-make/demo  # 对于Unix Makefiles预设
```

## 示例输出

### 配置和构建Release版本
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

### 运行程序
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

## 注意事项
- 需要CMake 3.19+。
- 预设名称区分大小写。
- `inherits`允许预设继承，减少重复。
- 构建目录由`binaryDir`指定，避免污染源目录。
- 对于大型项目，可添加更多预设，如交叉编译或特定工具链。

CMakePresets简化了构建流程，提高了开发效率。