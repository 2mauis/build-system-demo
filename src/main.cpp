#include "SubClass.h"
#include <iostream>

int main() {
    // 创建SubClass实例
    std::shared_ptr<SubClass> sub = std::make_shared<SubClass>("SubObject1");

    // 调用基类函数
    sub->normalFunction();
    sub->virtualFunction();
    sub->pureVirtualFunction();

    // 添加到map - 避免循环引用，不要添加自己
    sub->addToMap("key2", std::make_shared<SubClass>("SubObject2"));

    // 从map获取
    std::shared_ptr<BaseClass> retrieved = sub->getFromMap("key2");
    if (retrieved) {
        std::cout << "Retrieved object from map" << std::endl;
        retrieved->normalFunction();
        retrieved->virtualFunction();
        retrieved->pureVirtualFunction();
    }

    // 手动释放引用以触发析构
    sub.reset();
    retrieved.reset();

    // 强制刷新输出缓冲区
    std::cout << std::flush;

    return 0;
}