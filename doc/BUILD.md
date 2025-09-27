# 手动使用 CMake 构建（cmake -S . -B build && cmake --build build -j N）

本文档说明如何在本仓库中使用简单、可重复的单目录 CMake 构建命令手动构建项目。适用于本地开发和快速调试。

## 先决条件

- 已安装 CMake（推荐 3.19 及以上）。
- 已安装支持的 C++ 编译器（例如 clang 或 gcc）和相关工具链。
- 在 macOS 上，建议已安装 Xcode 或 Xcode 命令行工具。

## 推荐的最小构建步骤

在仓库根目录执行：

```bash
cmake -S . -B build && cmake --build build -j 6
```

说明：
- `-S .` 指定源代码目录（当前目录）。
- `-B build` 指定构建输出目录（这里使用 `build` 目录以保持源目录干净）。
- `cmake --build build` 使用 CMake 生成的构建系统（例如 Ninja 或 Make）实际构建项目。
- `-j 6` 是并行构建参数，6 可根据你的 CPU 核心数调整（例如 `-j $(nproc)` 或 `-j 8`）。

该命令是可复现的：所有中间文件都保存在 `build/` 下，清理构建只需删除该目录。

## 常见可选项

- 指定构建类型（Debug/Release/RelWithDebInfo）：

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release && cmake --build build -j 6
```

- 如果项目使用 CMakePresets（仓库可能提供），也可以使用：

```bash
cmake --preset release
cmake --build --preset release
```

- 清理构建目录：

```bash
rm -rf build && mkdir build
```

## 调试与常见问题

- 构建失败且提示找不到头文件或库：确认编译器路径与依赖已安装，检查 CMake 输出的 include 路径。
- 需要更多并行作业：把 `-j` 值调大（例如与你的 CPU 线程数相同），但注意内存占用会增加。
- 想要启用更多诊断信息：可以在配置时添加 `-DCMAKE_VERBOSE_MAKEFILE=ON` 或使用 `cmake --build build --verbose`。

## 运行

构建完成后，可运行可执行：

```bash
./build/demo
```

## 进一步的自动化

如需把相同的命令放到脚本或 CI，请将输出目录（`build/`）作为工作目录的一部分并缓存（例如在 CI 中缓存 `build` 下的外部依赖）。

---

更多 CMake 高级用法与预设示例，请参见：[doc/CMakePresets.md](doc/CMakePresets.md)
