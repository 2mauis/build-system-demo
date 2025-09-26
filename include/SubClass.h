#ifndef SUBCLASS_H
#define SUBCLASS_H

#include "BaseClass.h"
#include <memory>
#include <string>
#include <map>

class SubClass : public BaseClass {
public:
    SubClass(const std::string& name);
    virtual ~SubClass();

    // 实现纯虚函数
    void pureVirtualFunction() override;

    // 重写虚函数
    void virtualFunction() override;

    // 函数来添加和获取map中的对象
    void addToMap(const std::string& key, std::shared_ptr<BaseClass> obj);
    std::shared_ptr<BaseClass> getFromMap(const std::string& key);

private:
    class Impl {
    public:
        std::map<std::string, std::shared_ptr<BaseClass> > baseClassMap;
    };
    std::unique_ptr<Impl> pImpl;
};

#endif // SUBCLASS_H