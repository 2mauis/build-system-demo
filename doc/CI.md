# CI/CD 指南

[![English](https://img.shields.io/badge/Language-English-blue.svg)](doc/CI_EN.md) | [中文](doc/CI.md)

本项目配置了GitHub Actions，支持三种构建方式的手动触发编译。

## 支持的Workflows

### CMakePresets Workflow

- **文件**：`.github/workflows/cmake-presets.yml`
- **触发**：手动触发（workflow_dispatch）
- **支持的Preset**：default, release, debug
- **功能**：使用CMakePresets配置构建和测试

### Bazel Workflow

- **文件**：`.github/workflows/bazel.yml`
- **触发**：手动触发（workflow_dispatch）
- **功能**：使用Bazel直接构建和测试

### Bazelisk Workflow

- **文件**：`.github/workflows/bazelisk.yml`
- **触发**：手动触发（workflow_dispatch）
- **功能**：使用Bazelisk自动管理Bazel版本并构建测试

### Clang-Tidy Workflow

- **文件**：`.github/workflows/clang-tidy.yml`
- **触发**：手动触发（workflow_dispatch）
- **功能**：使用Clang-Tidy进行代码静态分析和质量检查

### Coverity SCA Workflow

- **文件**：`.github/workflows/coverity.yml`
- **触发**：手动触发（workflow_dispatch）
- **功能**：使用Coverity进行静态代码分析和安全检查
- **要求**：需要配置COVERITY_TOKEN和COVERITY_EMAIL secrets

## 如何使用

1. 进入GitHub仓库的Actions标签页
2. 选择想要的workflow
3. 点击"Run workflow"按钮
4. 根据需要调整输入参数
5. 点击"Run workflow"开始构建

## Workflow配置详情

### CMakePresets配置

此workflow使用CMake的preset功能，支持不同的构建配置：

- **default**：默认配置
- **release**：发布版本优化配置
- **debug**：调试版本配置

### Bazel配置

直接使用Bazel进行构建，支持自定义目标：

- **target**：要构建的Bazel目标（默认：`//:demo`）
- **test_target**：要运行的测试目标（可选，默认：空，不运行测试）

### Bazelisk配置

使用Bazelisk进行构建，自动管理Bazel版本：

- **target**：要构建的Bazel目标（默认：`//:demo`）
- **test_target**：要运行的测试目标（可选，默认：空，不运行测试）

### Clang-Tidy配置

使用Clang-Tidy进行代码静态分析：

- **build_type**：构建类型（Debug/Release，默认：Debug）
- **功能**：生成编译数据库并运行clang-tidy分析所有源文件

### Coverity配置

使用Coverity进行静态代码分析：

- **build_type**：构建类型（Debug/Release，默认：Debug）
- **功能**：运行Coverity分析并上传结果到Coverity服务器
- **要求**：需要在GitHub secrets中配置COVERITY_TOKEN和COVERITY_EMAIL

## 环境要求

所有workflow都在Ubuntu最新版本上运行，自动安装所需的依赖：

- CMake workflow：安装cmake和ninja-build
- Bazel workflow：从官方仓库安装Bazel
- Bazelisk workflow：下载并安装Bazelisk
- Clang-Tidy workflow：安装cmake、ninja-build和clang-tidy
- Coverity workflow：安装cmake、ninja-build，并下载Coverity工具

## GitHub Secrets配置

对于Coverity workflow，需要在仓库设置中配置以下secrets：

- `COVERITY_TOKEN`：Coverity扫描令牌
- `COVERITY_EMAIL`：与Coverity账户关联的邮箱地址

## 故障排除

如果workflow失败，请检查：

1. 代码语法错误
2. 依赖项缺失
3. 构建配置问题
4. 网络连接问题（下载依赖时）

### Clang-Tidy特定问题

- 确保所有头文件路径正确
- 检查clang-tidy配置和警告级别

### Coverity特定问题

- 确认COVERITY_TOKEN和COVERITY_EMAIL已正确配置
- 检查Coverity账户权限
- 确认项目已在Coverity中注册

可以在Actions标签页查看详细的日志输出。
