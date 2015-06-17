#include <deque>
#include <iostream>

class MyClass {
    public:
    typedef std::deque<MyClass> List;
    
    MyClass(){
        std::cout << "Hello, World!\n";
    }
    ~MyClass() {}
};


int main()
{
    MyClass::List L;
    
    MyClass C;
    L.push_back(C);
    MyClass D = C;
    std::cout << "How many \"Hello, World!\\n\" ? :-)\n";
    return 0;
}