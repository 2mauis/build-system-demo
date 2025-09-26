#ifndef BASECLASS_H
#define BASECLASS_H

#include <memory>
#include <string>

class BaseClass {
public:
    BaseClass(const std::string& name);
    virtual ~BaseClass();

    // 禁用拷贝构造和赋值
    BaseClass(const BaseClass&) = delete;
    BaseClass& operator=(const BaseClass&) = delete;

    // 纯虚函数
    virtual void pureVirtualFunction() = 0;

    // 虚函数
    virtual void virtualFunction();

    // 普通函数
    void normalFunction();

protected:
    class Impl {
    public:
        Impl(const std::string& name) : name(name) {}
        std::string name;
    };
    std::unique_ptr<Impl> pImpl;

    // 受保护的构造函数，用于子类自定义Impl
    BaseClass(std::unique_ptr<Impl> impl);
};;

#endif // BASECLASS_H