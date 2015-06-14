#include <iostream>
#include <ostream>

struct B
{
    virtual void g() { std::cout << "B::g()" << std::endl; }
    void f() { std::cout << "B::f()" << std::endl; }
};

class D1 : public B
{
    // No estoy sobrecargando dicha función virtual, sólo le estoy cambiando el especificador de acceso (a private).
    // Lo que hace ese `using` es "heredar explícitamente a B::g`, indicándole donde quiero que lo herede.
    using B::g;
  
protected:
    // No estoy oscureciendo a B::f, solo le estoy cambiando el especificador de acceso (a protected).
    using B::f;
};


int main()
{
    D1 d;
    B& rb = d;
    
    // d.g(); Error, B::g es privado desde D3.
    // d.f(); Error B::f es privado desde D3.
    
    // Mismo caso de antes, aunque más sencillo, `f` no es virtual así que nada nuevo. Se ejecuta sin problemas.
    // `g` es virtual, pero no pasa nada, no está sobrecargada (B::f), y si lo estuviera, ejecutaría D1::g.
    // sin problemas.
    rb.g();
    rb.f();
}