#include <memory>

class MyClass {
public:
    std::unique_ptr<int> p;
};

int main() {
    MyClass b(MyClass());
}