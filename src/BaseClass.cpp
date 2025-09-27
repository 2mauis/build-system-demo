#include "BaseClass.h"
#include <iostream>
#include <string>
#include <memory>

// 定义 Impl（PIMPL），放在 .cpp 隐藏实现细节
class BaseClass::Impl {
public:
  Impl(std::string_view name) : name(std::string(name)) {}
  std::string name;
  friend class BaseClass;
};

// 公共构造函数，使用 make_unique
BaseClass::BaseClass(std::string_view name) noexcept : pImpl(std::make_unique<Impl>(name)) {
  std::cout << "BaseClass constructor called for " << pImpl->name << std::endl;
}

// 受保护构造函数实现
BaseClass::BaseClass(std::unique_ptr<Impl> impl) noexcept : pImpl(std::move(impl)) {
  std::cout << "BaseClass protected constructor called" << std::endl;
}

BaseClass::~BaseClass() noexcept = default;

void BaseClass::virtualFunction() noexcept {
  std::cout << "BaseClass virtual function called by " << pImpl->name << std::endl;
}

void BaseClass::normalFunction() noexcept {
  std::cout << "BaseClass normal function called by " << pImpl->name << std::endl;
}

const std::string &BaseClass::implName() const { return pImpl->name; }