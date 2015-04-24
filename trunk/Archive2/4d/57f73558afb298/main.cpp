#include <iostream>

class A
{
public:
    A():i(1) {}
    
    int i;
};

void test(A** a)
{
    A* b = new A();
    b->i = 3;
    
    *a = b;
}

int main()
{    
    A* a = NULL ;
    
    test(&a);
    
    std::cout << a->i << std::endl;
    
    delete(a);
    
    return 0;
}