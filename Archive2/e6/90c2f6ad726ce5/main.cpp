#include <iostream>
#include <memory>

struct MyClass {
    MyClass() = default;
    
    MyClass(const MyClass &other) {
        lastCopied = std::addressof(other);
    }
    
    const MyClass *operator&() const {
        return lastCopied;
    }
    
    bool isObject(MyClass a)
    {
        if (&a==this) return true;
        else return false;
    }
    
private:
    static const MyClass *lastCopied; 
};

const MyClass *MyClass::lastCopied;

int main() {
    MyClass c;
    std::cout << std::boolalpha << c.isObject(c);
}
