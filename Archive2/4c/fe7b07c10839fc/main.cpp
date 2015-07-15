#include <vector>
#include <iostream>
 
struct B {
    void foo() const {
        std::cout << "Hello world" << std::endl;
    }

};
struct D : B {
    void foo() const {
        std::cout << "Goodbye world" << std::endl;
    }
};
 
enum class E { ONE, TWO, THREE };
enum EU { ONE, TWO, THREE };
 
int main()
{
    D d;
    D* dPtr = &d;
    D** dPtrPtr = &dPtr;
    
    if (dynamic_cast<B*>(*dPtrPtr)) {
        B** res = reinterpret_cast<B**>(dPtrPtr);
        (*res)->foo();
        (*dPtrPtr)->foo();
    }
}