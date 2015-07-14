#include <iostream>
#include <string>
#include <cstring>

struct ClassA
{
    
};

struct ClassB
{
    ClassA* memberA;  
};

struct ClassC
{
    ClassB* memberB;  
    
    void create()
    {
        ClassB b;
        memset(&b, 0, sizeof(ClassB));
    
        ClassA* a = new ClassA();
        b.memberA = a;
        
        std::cout << &b << std::endl;
        std::cout << b.memberA << std::endl;
        
        memberB = &b;
        
        std::cout << memberB << std::endl;
        std::cout << memberB->memberA << std::endl;
    }
    
    void access()
    {
        std::cout << memberB << std::endl;
        std::cout << memberB->memberA << std::endl;
    }
    
    
};

int main() {
    
      ClassC c;
      c.create();
      c.access();
    
    
    return 0;
}
