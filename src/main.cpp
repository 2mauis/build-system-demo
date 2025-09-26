#include "SubClass.h"
#include <iostream>

int main() {
    // 创建SubClass实例
    std::shared_ptr<SubClass> sub = std::make_shared<SubClass>("SubObject1");

    // 调用基类函数
    sub->normalFunction();
    sub->virtualFunction();
    sub->pureVirtualFunction();

    // 添加到map
    sub->addToMap("key1", sub);

    sub->addToMap("key2", std::make_shared<SubClass>("SubObject2"));

    // 从map获取
    std::shared_ptr<BaseClass> retrieved = sub->getFromMap("key1");
    if (retrieved) {
        std::cout << "Retrieved object from map" << std::endl;
        retrieved->normalFunction();
        retrieved->virtualFunction();
        retrieved->pureVirtualFunction();
    }

    return 0;
}