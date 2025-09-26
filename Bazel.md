# Bazel 使用方式和原理

## 什么是Bazel？

Bazel是一个开源的构建和测试工具，由Google开发。它支持多语言项目（C++、Java、Python等），强调可扩展性、性能和正确性。Bazel适用于大型代码库，能够处理复杂的依赖关系和并行构建。

### 核心特性
- **增量构建**：只重新构建变更的部分。
- **分布式构建**：支持远程执行和缓存。
- **多语言支持**：内置规则支持多种编程语言。
- **可扩展**：通过自定义规则扩展功能。
- **沙盒化**：构建在隔离环境中运行，确保可重现性。

## Bazel原理

### 构建图（Build Graph）
- Bazel将项目建模为有向无环图（DAG），节点是目标（targets），边是依赖关系。
- 目标包括库（cc_library）、二进制文件（cc_binary）等。
- Bazel分析依赖，确定构建顺序。

### 增量构建
- 使用内容哈希检测文件变化。
- 只重新构建受影响的目标。
- 缓存构建产物，避免重复工作。

### 模块系统（Bzlmod）
- Bazel 8.x引入Bzlmod，用于管理外部依赖。
- 默认启用，但可禁用以使用WORKSPACE模式。
- 模块定义在MODULE.bazel文件中。

### WORKSPACE模式
- 传统方式，使用WORKSPACE文件定义外部依赖。
- 通过http_archive等规则下载依赖。
- 在Bazel 9中将被移除，推荐迁移到Bzlmod。

### 工具链和平台
- Bazel使用工具链（toolchains）抽象编译器、链接器等。
- 平台（platforms）定义目标环境（如操作系统、架构）。
- 自动选择合适的工具链。

## 在项目中的使用方式

### 项目结构
```
class_test/
├── WORKSPACE          # 定义工作空间
├── BUILD              # 定义构建目标
├── .bazelrc           # Bazel配置
├── include/           # 头文件
├── src/               # 源文件
└── .gitignore         # 忽略构建产物
```

### WORKSPACE文件
```starlark
workspace(name = "class_test")
```
- 定义工作空间名称。
- 可添加外部依赖规则，如http_archive。

### BUILD文件
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
- **cc_library**：定义库目标。
- **cc_binary**：定义可执行目标。
- **deps**：指定依赖。
- **strip_include_prefix**：处理头文件路径。

### .bazelrc配置
```bash
common --enable_bzlmod=false
common --enable_workspace=true
```
- 禁用Bzlmod，使用WORKSPACE模式。
- 避免下载无关模块，优化构建速度。

### 常用命令
- **构建**：`bazel build //:demo`
- **运行**：`bazel run //:demo`
- **测试**：`bazel test //:target`（如果有测试）
- **查询依赖**：`bazel query 'deps(//:demo)'`
- **清理**：`bazel clean` 或 `bazel clean --expunge`
- **信息**：`bazel info output_base`（查看输出目录）

### 构建过程
1. **分析**：解析BUILD文件，构建依赖图。
2. **执行**：并行执行构建步骤。
3. **缓存**：存储中间结果。
4. **输出**：生成目标文件在bazel-bin/等目录。

### 优势
- **速度**：增量构建和缓存减少时间。
- **可扩展**：处理大型项目。
- **一致性**：沙盒化确保构建可重现。
- **多平台**：支持跨平台构建。

### 注意事项
- WORKSPACE模式即将弃用，考虑迁移到Bzlmod。
- 首次构建可能下载工具链，耗时较长。
- 使用.bazelrc优化配置，如禁用无关模块。

### 示例输出
```
$ bazel build //:demo
INFO: Analyzed target //:demo (59 packages loaded, 270 targets configured).
INFO: Found 1 target...
Target //:demo up-to-date:
  bazel-bin/demo
INFO: Elapsed time: 7.549s, Critical Path: 0.88s
INFO: Build completed successfully, 17 total actions
```

Bazel提供了强大的构建能力，适合现代软件开发。通过理解其原理，可以更好地利用其特性优化项目构建。