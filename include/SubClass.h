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
    // SubClass不使用自己的Impl，而是直接使用BaseClass的pImpl
    // 但为了扩展性，我们可以添加额外的成员函数来处理SubClass特有的数据
    std::map<std::string, std::shared_ptr<BaseClass> > baseClassMap;
};

#endif // SUBCLASS_H