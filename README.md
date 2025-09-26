# C++ 类继承演示：纯虚函数、虚函数和普通函数

本项目演示了C++中基类继承的概念，包括纯虚函数、虚函数和普通函数的使用方法和区别。通过具体的代码实例，展示这些函数在类层次结构中的行为。

## 项目结构

- `BaseClass`: 基类，包含纯虚函数、虚函数和普通函数。
- `SubClass`: 派生类，继承自`BaseClass`，实现纯虚函数，重写虚函数。
- `main.cpp`: 主函数，创建对象并调用函数，展示多态性。

## 构建和运行

### 使用CMake
- 安装CMake 3.19+。
- 配置：`cmake --preset release`
- 构建：`cmake --build --preset release`
- 测试：`ctest --preset release`
- 运行：`./build/demo`

详细请参考 [CMakePresets.md](CMakePresets.md)。

### 使用Bazel

- 安装Bazel或[Bazelisk](Bazelisk.md)（推荐）。
- 构建：`bazel build //:demo`
- 运行：`bazel run //:demo`

详细请参考 [Bazel.md](Bazel.md) 和 [Bazelisk.md](Bazelisk.md)。

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

详细的CI/CD配置和使用说明请参考 [CI.md](CI.md)。

## Changelog

### Recent Commits

- `a6532f9` Fix Bazel workflows: remove default test target that doesn't exist
- `c3ba48f` Update changelog with latest commit
- `4e5423e` Extract CI/CD documentation to separate CI.md file and update README reference
- `bb34efd` Add CI/CD section to README documenting GitHub Actions workflows
- `7a7ae49` Add GitHub Actions workflows for CMakePresets, Bazel, and Bazelisk builds
- `3b9acaa` Update README with latest commit record
- `5960f71` Add Bazelisk documentation and update README with Bazelisk link
- `e2a25cb` Add CMakePresets, CTest integration, and documentation updates
- `49744ee` Initial commit: C++ class inheritance demo with CMake and Bazel build support
