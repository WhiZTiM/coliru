#include <iostream>

using namespace std;

struct A
{
    A operator+(A const& a) { cout << 1 << endl; return A(); }  
};

A operator+(A const& a, A const& b) { cout << 5 << endl; return A(); }

struct B
{
    B operator+(B const& a) const { cout << 3 << endl; return B(); }
};

B operator+(B const& a, B const& b) { cout << 4 << endl; return B(); }

int main()
{
    A a, b;
    B c, d;
    
    // ¿Qué imprime en ambos casos? ¿O sucede un error? ¿Y por qué?
    a + b;
    c + d;
    
    return 0;
}

