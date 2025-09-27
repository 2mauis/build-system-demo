#ifndef SUBCLASS_H
#define SUBCLASS_H

#include "BaseClass.h"
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>

class SubClass : public BaseClass {
public:
    SubClass(std::string_view name);
    virtual ~SubClass() noexcept;

    // 实现纯虚函数
    void pureVirtualFunction() override;

    // 重写虚函数
    void virtualFunction() noexcept override;

    // 函数来添加和获取map中的对象
    // convenience overload: accept by-value and forward to rvalue-ref implementation
    // keeps backward compatibility while allowing callers to move for performance
    void addToMap(std::string key, std::shared_ptr<BaseClass> obj);

    // (rvalue-ref overload removed to avoid ambiguity; use the by-value overload and std::move for performance)
    std::shared_ptr<BaseClass> getFromMap(const std::string& key);

private:
    // SubClass有自己的PIMPL实现（前向声明，定义放在 .cpp）
    class Impl;
    std::unique_ptr<Impl> pImplSub;

    // internal implementation target for addToMap to avoid overload ambiguity
    void addToMapImpl(std::string key, std::shared_ptr<BaseClass> obj);

    // SubClass同时保留一个unordered_map来管理BaseClass对象
    // 使用 weak_ptr 存储以避免循环引用；getFromMap 会 lock() 返回 shared_ptr
    std::unordered_map<std::string, std::weak_ptr<BaseClass>> baseClassMap;
};

#endif // SUBCLASS_H