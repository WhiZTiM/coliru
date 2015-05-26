#include <iostream>
#include <algorithm>
#include <functional>
#include <list>

struct MyClass {
    int value;

    MyClass(int x) : value(x) {}
    bool Condition() {
        return (value > 7500);
    }
};

int main() {
    std::list<MyClass> info1 { 183, 37643, 276, 0, -218763, 82176 };
    info1.remove_if(std::mem_fn(&MyClass::Condition));
    
    for (auto i : info1)
        std::cout << i.value << ' ';
}
