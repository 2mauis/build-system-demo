#ifndef BASECLASS_H
#define BASECLASS_H

#include <string>

class BaseClass {
public:
    BaseClass(const std::string& name);
    virtual ~BaseClass();

    // 纯虚函数
    virtual void pureVirtualFunction() = 0;

    // 虚函数
    virtual void virtualFunction();

    // 普通函数
    void normalFunction();

protected:
    std::string name;
};

#endif // BASECLASS_H