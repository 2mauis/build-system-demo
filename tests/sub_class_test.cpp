#include "SubClass.h"
#include <memory>
#include <cassert>

int main() {
    auto sub = std::make_shared<SubClass>("test-sub");
    // exercise methods
    sub->virtualFunction();
    sub->pureVirtualFunction();
    sub->normalFunction();

    auto other = std::make_shared<SubClass>("other");
    sub->addToMap("k", other);
    auto lookup = sub->getFromMap("k");
    assert(lookup != nullptr);
    return 0;
}
