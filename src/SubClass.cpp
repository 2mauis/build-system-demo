#include "SubClass.h"
#include <iostream>

SubClass::SubClass(const std::string& name) : BaseClass(name) {
    std::cout << "SubClass constructor called for " << name << std::endl;
}

SubClass::~SubClass() {
    std::cout << "SubClass destructor called for " << pImpl->name << std::endl;
}

void SubClass::pureVirtualFunction() {
    std::cout << "SubClass pure virtual function implemented by " << pImpl->name << std::endl;
}

void SubClass::virtualFunction() {
    std::cout << "SubClass virtual function overridden by " << pImpl->name << std::endl;
}

void SubClass::addToMap(const std::string& key, std::shared_ptr<BaseClass> obj) {
    baseClassMap[key] = obj;
}

std::shared_ptr<BaseClass> SubClass::getFromMap(const std::string& key) {
    if (baseClassMap.find(key) != baseClassMap.end()) {
        return baseClassMap[key];
    }
    return nullptr;
}