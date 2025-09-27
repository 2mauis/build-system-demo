#include "SubClass.h"
#include <iostream>
#include <memory>

// SubClass-specific Impl definition (kept private in .cpp)
class SubClass::Impl {
public:
    Impl() = default;
    int counter = 0;
    friend class SubClass;
};

SubClass::SubClass(std::string_view name) : BaseClass(name) {
    std::cout << "SubClass constructor called for " << implName() << std::endl;
    pImplSub = std::make_unique<Impl>();
    // 预先为 map 保留一些槽以减少重哈希（根据预期规模调整）
    baseClassMap.reserve(8);
}

SubClass::~SubClass() noexcept {
    std::cout << "SubClass destructor called for " << implName() << std::endl;
}

void SubClass::pureVirtualFunction() {
    std::cout << "SubClass pure virtual function implemented by " << implName() << std::endl;
}

void SubClass::virtualFunction() noexcept {
    std::cout << "SubClass virtual function overridden by " << implName() << std::endl;
}

void SubClass::addToMap(std::string key, std::shared_ptr<BaseClass> obj) {
    // by-value overload forwards to a single implementation point
    addToMapImpl(std::move(key), std::move(obj));
}

void SubClass::addToMapImpl(std::string key, std::shared_ptr<BaseClass> obj) {
    // single implementation point: store weak_ptr
    baseClassMap.emplace(std::move(key), std::weak_ptr<BaseClass>(std::move(obj)));
}

std::shared_ptr<BaseClass> SubClass::getFromMap(const std::string& key) {
    if (auto it = baseClassMap.find(key); it != baseClassMap.end()) {
        if (auto sp = it->second.lock()) {
            return sp;
        }
        // 如果 weak_ptr 已过期，则擦除条目
        baseClassMap.erase(it);
    }
    return nullptr;
}