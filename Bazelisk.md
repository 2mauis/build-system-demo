# Bazelisk 使用指南

[![English](https://img.shields.io/badge/Language-English-blue.svg)](Bazelisk_EN.md) | [中文](Bazelisk.md)

## 什么是Bazelisk？

Bazelisk是一个开源工具，用于自动管理和运行正确的Bazel版本。它是Bazel的版本管理器，类似于其他语言的版本管理器（如nvm for Node.js或rbenv for Ruby）。

### 核心特性

- **自动版本选择**：根据项目配置自动下载和使用合适的Bazel版本。
- **无缝集成**：与标准Bazel命令完全兼容，无需修改现有脚本。
- **团队一致性**：确保所有开发者使用相同Bazel版本，避免版本冲突。
- **CI/CD友好**：在持续集成环境中自动处理版本管理。

### 与Bazel的区别

- **Bazel**：直接的构建工具，需要手动安装特定版本。
- **Bazelisk**：版本管理器，自动处理Bazel版本选择和安装。

## 安装步骤

### macOS (使用Homebrew)

```bash
# 如果已安装Bazel，先unlink
brew unlink bazel

# 安装Bazelisk
brew install bazelisk

# 验证安装
bazelisk version
```

### Linux

```bash
# 下载最新版本
curl -L https://github.com/bazelbuild/bazelisk/releases/latest/download/bazelisk-linux-amd64 -o bazelisk
chmod +x bazelisk

# 移动到PATH中
sudo mv bazelisk /usr/local/bin/

# 验证安装
bazelisk version
```

### Windows

```powershell
# 使用Chocolatey
choco install bazelisk

# 或下载二进制文件
# https://github.com/bazelbuild/bazelisk/releases
```

## 使用步骤

### 基本命令

Bazelisk命令与Bazel完全相同：

```bash
# 构建目标
bazelisk build //:target

# 运行目标
bazelisk run //:target

# 测试
bazelisk test //:target

# 清理
bazelisk clean

# 查询
bazelisk query 'deps(//:target)'

# 显示版本
bazelisk version
```

### 版本选择机制

Bazelisk按以下优先级选择Bazel版本：

1. **.bazelversion文件**：项目根目录中的文件指定版本。

   ```text
   8.4.1
   ```

2. **WORKSPACE.bazelrc或.bazelrc**：配置中的`USE_BAZEL_VERSION`。

   ```text
   common --repo_env=USE_BAZEL_VERSION=8.4.1
   ```

3. **MODULE.bazel**：Bzlmod中的`bazel`字段。

   ```starlark
   bazel = "8.4.1"
   ```

4. **自动选择**：如果未指定，使用最新稳定版本。

### 项目配置示例

#### .bazelversion文件

在项目根目录创建`.bazelversion`：

```text
8.4.1
```

#### .bazelrc配置

```bash
# 指定Bazel版本
common --repo_env=USE_BAZEL_VERSION=8.4.1

# 其他配置
common --enable_bzlmod=true
common --enable_workspace=true
```

## 在项目中的应用

### 示例项目结构

```text
my_project/
├── .bazelversion    # 指定Bazel版本
├── .bazelrc         # Bazel配置
├── WORKSPACE        # 工作空间定义
├── BUILD            # 构建规则
└── src/             # 源代码
```

### 构建流程

```bash
# 进入项目目录
cd my_project

# 构建（自动下载合适Bazel版本）
bazelisk build //:demo

# 运行
bazelisk run //:demo

# 测试
bazelisk test //:demo_test
```

### CI/CD集成

在GitHub Actions中使用：

```yaml
- name: Setup Bazelisk
  run: |
    curl -L https://github.com/bazelbuild/bazelisk/releases/latest/download/bazelisk-linux-amd64 -o bazelisk
    chmod +x bazelisk
    sudo mv bazelisk /usr/local/bin/

- name: Build
  run: bazelisk build //:target
```

## 优势和最佳实践

### 优势

- **版本一致性**：团队成员自动使用相同Bazel版本。
- **简化安装**：无需手动管理Bazel版本。
- **向后兼容**：现有Bazel脚本无需修改。
- **自动更新**：可以轻松升级到新版本。

### 最佳实践

- **固定版本**：在`.bazelversion`中指定确切版本，确保可重现构建。
- **定期更新**：定期更新Bazel版本以获得最新功能和修复。
- **文档化**：在项目README中说明使用的Bazel版本。
- **CI配置**：在CI中明确指定版本，避免意外升级。

## 故障排除

### 常见问题

- **版本不匹配**：检查`.bazelversion`文件。
- **下载失败**：检查网络连接，重试命令。
- **权限问题**：确保有权限下载和安装Bazel。

### 获取帮助

- [Bazelisk GitHub](https://github.com/bazelbuild/bazelisk)
- [Bazel文档](https://bazel.build)

Bazelisk简化了Bazel的版本管理，使构建过程更加可靠和一致。