#include <iostream>

void* foo(struct Test* t)
{
    return t; 
}

void* oof(Test* t)
{
    return t; 
}


struct Test
{
    int i; 
};

int main()
{
    Test t = {1}; 
    
    auto vt = foo(&t); 
    ((Test*)vt)->i += 1;
    vt = oof(&t); 
    std::cout << ((Test*)vt)->i << std::endl;
}
