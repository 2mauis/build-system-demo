#include "BaseClass.h"
#include <iostream>

BaseClass::BaseClass(const std::string& name) : pImpl(new Impl(name)) {
    std::cout << "BaseClass constructor called for " << name << std::endl;
}

BaseClass::~BaseClass() = default;

void BaseClass::virtualFunction() {
    std::cout << "BaseClass virtual function called by " << pImpl->name << std::endl;
}

void BaseClass::normalFunction() {
    std::cout << "BaseClass normal function called by " << pImpl->name << std::endl;
}