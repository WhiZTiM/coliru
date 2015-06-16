#include <iostream>
#include <array>


template<typename A, typename B>
void add(A* a, B* b)
{
    a->n += b->n;
    a->n += b->n;
    a->n += b->n;
    a->n += b->n;
}


template<typename A, typename B>
void test()
{
    A a;
    B& b = (B&)(a);
        
    add(&a, &b);
    add(&a, &b);
    
    std::cout << " a=" << a.n << " b=" << b.n << std::endl;
}


int main()
{

    struct A { int n = 1; };
    struct B { int n = 1; };

    test<A, A>(); // overlapping data, same types
    test<A, B>(); // overlapping data, different types
}