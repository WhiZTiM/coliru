#include <iostream>
#include <memory>

struct MyClass {
    MyClass() = default;
    
    MyClass(const MyClass &other) {
        copiedFrom = std::addressof(other);
    }
    
    const MyClass *operator&() const {
        return copiedFrom;
    }
    
    bool isObject(MyClass a)
    {
        if (&a==this) return true;
        else return false;
    }
    
private:
    const MyClass *copiedFrom{}; 
};

int main() {
    MyClass c;
    std::cout << std::boolalpha << c.isObject(c);
}
