#include <iostream>
#include <ostream>

struct B
{
    virtual void g() { std::cout << "B::g()" << std::endl; }
};

class D1 : public B
{
    void g () { std::cout << "D1::g()" << std::endl; }
};

class D2 : public D1
{
public:
    void g()
    {
        std::cout << "D2::g()" << std::endl;
        // D1::g(); // Error D1::g es innacesible (privado).
    }
};


int main()
{
    D2 d;
    B& rb = d;
    
    d.g(); // Ahora es público desde D2. Imprime D2::g().
    
    // Sí, imprime D2::g(). Y sí, D2::g() está sobrecargando a D1::g(), aunque sea
    // innacesible desde D2. Recuerda, innacesible significa "que no puedo escribir su nombre"
    // (llamarlo explícitamente), pero si puede ser sobrecargada y ejecutable desde un punto
    // público (B).
    rb.g();
}