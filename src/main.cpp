#include "SubClass.h"
#include <iostream>

int main() {
    using namespace std::literals;

    // 创建SubClass实例
    auto sub = std::make_shared<SubClass>("SubObject1"sv);

    // 调用基类和子类函数
    sub->normalFunction();
    sub->virtualFunction();
    sub->pureVirtualFunction();

    // 添加到map（构造 shared_ptr 后通过 std::move 传入以使用移动语义）
    auto child = std::make_shared<SubClass>("SubObject2"sv);
    std::string key = "key2";
    sub->addToMap(std::move(key), std::move(child));

    // 从map获取
    if (auto retrieved = sub->getFromMap("key2"); retrieved) {
        std::cout << "Retrieved object from map" << std::endl;
        retrieved->normalFunction();
        retrieved->virtualFunction();
        retrieved->pureVirtualFunction();
    }

    // 手动释放引用以触发析构（可选）
    sub.reset();

    std::cout << std::flush;
    return 0;
}