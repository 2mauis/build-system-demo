#ifndef BASECLASS_H
#define BASECLASS_H

#include <memory>
#include <string>
#include <string_view>

class BaseClass {
public:
  BaseClass(std::string_view name) noexcept;
  virtual ~BaseClass() noexcept;

  // 禁用拷贝构造和赋值
  BaseClass(const BaseClass &) = delete;
  BaseClass &operator=(const BaseClass &) = delete;

  // 纯虚函数
  virtual void pureVirtualFunction() = 0;

  // 虚函数
  virtual void virtualFunction() noexcept;

  // 普通函数
  void normalFunction() noexcept;

protected:
  // 嵌套类前向声明（完整定义放在 .cpp）
  class Impl;

  // 受保护的构造函数，用于子类自定义Impl
  BaseClass(std::unique_ptr<Impl> impl) noexcept;

  std::unique_ptr<Impl> pImpl;

  // 受保护的访问器，子类可以通过它获取名称，无需知道Impl定义
  const std::string &implName() const;
};

#endif // BASECLASS_H