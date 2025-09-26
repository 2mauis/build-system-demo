#include "SubClass.h"
#include <iostream>

SubClass::SubClass(const std::string& name) : BaseClass(name), pImpl(new Impl()) {
    std::cout << "SubClass constructor called for " << name << std::endl;
}

SubClass::~SubClass() {
    std::cout << "SubClass destructor called for object" << std::endl;
}

void SubClass::pureVirtualFunction() {
    std::cout << "SubClass pure virtual function implemented by object" << std::endl;
}

void SubClass::virtualFunction() {
    std::cout << "SubClass virtual function overridden by object" << std::endl;
}

void SubClass::addToMap(const std::string& key, std::shared_ptr<BaseClass> obj) {
    pImpl->baseClassMap[key] = obj;
}

std::shared_ptr<BaseClass> SubClass::getFromMap(const std::string& key) {
    if (pImpl->baseClassMap.find(key) != pImpl->baseClassMap.end()) {
        return pImpl->baseClassMap[key];
    }
    return nullptr;
}