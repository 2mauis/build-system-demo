#include "BaseClass.h"
#include <iostream>

BaseClass::BaseClass(const std::string& name) : name(name) {
    std::cout << "BaseClass constructor called for " << name << std::endl;
}

BaseClass::~BaseClass() {
    std::cout << "BaseClass destructor called for " << name << std::endl;
}

void BaseClass::virtualFunction() {
    std::cout << "BaseClass virtual function called by " << name << std::endl;
}

void BaseClass::normalFunction() {
    std::cout << "BaseClass normal function called by " << name << std::endl;
}