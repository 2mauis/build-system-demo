

# C++ 类继承演示：纯虚函数、虚函数和普通函数 (CMake/Bazel构建系统演示)

> **本工程采用 Copilot Agent 模式构建并测试** - 整个项目（包括代码、构建系统、CI/CD、文档）均由Grok Code Fast (Preview) 模型和GPT-5 Mini自动生成和配置。

[![English](https://img.shields.io/badge/Language-English-blue.svg)](README_EN.md) | [中文](README.md)

本项目演示了C++中基类继承的概念，包括纯虚函数、虚函数和普通函数的使用方法和区别。通过具体的代码实例，展示这些函数在类层次结构中的行为。同时演示了现代C++项目的完整构建系统配置，包括CMake、CMakePresets、Bazel、Bazelisk等多种构建工具。

## 项目结构

- `BaseClass`: 基类，包含纯虚函数、虚函数和普通函数。
- `SubClass`: 派生类，继承自`BaseClass`，实现纯虚函数，重写虚函数。
- `main.cpp`: 主函数，创建对象并调用函数，展示多态性。

## 构建和运行

### 使用CMake

#### 先决条件

- 已安装 CMake（推荐 3.19 及更高）。
- 已安装一个兼容的 C++ 编译器（如 clang 或 gcc）和必要的系统工具链。

#### 快速开始（手动构建）

这是最简单、跨平台的手动构建流程，将所有中间产物放到 `build/` 目录：

```bash
cmake -S . -B build && cmake --build build -j 6
```

示例说明：`-S .` 指定源码目录，`-B build` 指定输出目录；`-j 6` 为并行构建的线程数，按需调整。

更多手动构建的细节与排错见：[doc/CMakeBuild.md](doc/CMakeBuild.md)

#### 使用 CMakePresets（推荐用于 CI / 一致性）

仓库也可能提供 CMakePresets（见 `doc/CMakePresets.md`），使用预设可以让配置和构建在本地与 CI 之间保持一致：

```bash
cmake --preset release
cmake --build --preset release
```

#### 构建类型

你可以通过 `-DCMAKE_BUILD_TYPE=Debug|Release|RelWithDebInfo` 指定单配置生成器的构建类型，或使用预设在多配置环境中控制行为。

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release && cmake --build build -j 6
```

#### 测试

构建后运行测试：

```bash
ctest --test-dir build
```

如果使用 presets：

```bash
ctest --preset release
```

#### 运行

构建完成后可直接运行可执行文件：

```bash
./build/demo
```

#### 常见问题与故障排查

- 找不到头文件或库：检查 CMake 输出的 include 与 link 路径，确保依赖已安装或正确设置路径。
- 构建失败并显示编译器错误：先尝试清理构建目录（`rm -rf build`）并重新配置；在 macOS 上确认 Xcode 命令行工具已安装。
- 想要更多构建输出：在配置时使用 `-DCMAKE_VERBOSE_MAKEFILE=ON`，或者 `cmake --build build --verbose`。

更多关于 presets 和示例请见：[doc/CMakePresets.md](doc/CMakePresets.md)

### 使用Bazel

- 安装Bazel或[Bazelisk](doc/Bazelisk.md)（推荐）。
- 构建：`bazel build //:demo`
- 运行：`bazel run //:demo`

详细请参考 [Bazel.md](doc/Bazel.md) 和 [Bazelisk.md](doc/Bazelisk.md)。

## 函数类型解释

### 1. 普通函数 (Normal Function)

#### 定义
普通函数是类中的标准成员函数，没有`virtual`关键字。它们在编译时绑定（静态绑定），不支持运行时多态。

#### 使用方法
- 在基类中定义函数体。
- 派生类可以重定义（隐藏）同名函数，但不构成重写（override）。
- 通过对象指针或引用调用时，调用的是指针/引用类型对应的函数。

#### 区别
- 不支持多态：调用取决于指针类型，而不是对象实际类型。
- 效率较高，因为没有虚函数表开销。

#### 实例
在`BaseClass`中：
```cpp
void normalFunction() {
    std::cout << "BaseClass normal function called by " << name << std::endl;
}
```
在`main.cpp`中调用：
```cpp
sub->normalFunction();  // 输出: BaseClass normal function called by SubObject1
```
即使通过`BaseClass`指针调用，也执行基类的实现。

### 2. 虚函数 (Virtual Function)

#### 定义
虚函数使用`virtual`关键字声明，可以在派生类中重写。支持运行时多态，通过虚函数表（vtable）实现动态绑定。

#### 使用方法
- 在基类中声明为`virtual`，可以提供默认实现。
- 派生类使用`override`关键字重写（可选）。
- 通过基类指针或引用调用时，执行实际对象类型的函数。

#### 区别
- 支持多态：调用取决于对象实际类型。
- 允许派生类选择是否重写。
- 有轻微的运行时开销。

#### 实例
在`BaseClass`中：
```cpp
virtual void virtualFunction() {
    std::cout << "BaseClass virtual function called by " << name << std::endl;
}
```
在`SubClass`中重写：
```cpp
void virtualFunction() override {
    std::cout << "SubClass virtual function overridden by " << name << std::endl;
}
```
在`main.cpp`中调用：
```cpp
sub->virtualFunction();  // 输出: SubClass virtual function overridden by SubObject1
```
通过`BaseClass`指针调用时，也执行`SubClass`的版本。

### 3. 纯虚函数 (Pure Virtual Function)

#### 定义
纯虚函数是声明为`virtual`并以`= 0`结尾的函数，没有实现。使类成为抽象类，不能实例化。强制派生类实现该函数。

#### 使用方法
- 在基类中声明：`virtual void func() = 0;`
- 派生类必须提供实现，否则无法实例化。
- 用于定义接口，确保派生类实现特定行为。

#### 区别
- 必须在派生类中实现，否则编译错误。
- 使基类抽象，不能创建对象。
- 强调接口设计，支持多态。

#### 实例
在`BaseClass`中：
```cpp
virtual void pureVirtualFunction() = 0;
```
在`SubClass`中实现：
```cpp
void pureVirtualFunction() override {
    std::cout << "SubClass pure virtual function implemented by " << name << std::endl;
}
```
在`main.cpp`中调用：
```cpp
sub->pureVirtualFunction();  // 输出: SubClass pure virtual function implemented by SubObject1
```

## 运行演示

编译和运行项目：
```bash
cd build
make
./demo
```

输出示例：
```
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

## 总结

- **普通函数**：静态绑定，无多态，用于具体实现。
- **虚函数**：动态绑定，支持可选重写，用于多态行为。
- **纯虚函数**：强制实现，定义接口，用于抽象设计。

通过本项目，可以直观理解这些函数在继承和多态中的作用。

## CI/CD

详细的CI/CD配置和使用说明请参考 [CI.md](doc/CI.md)。

