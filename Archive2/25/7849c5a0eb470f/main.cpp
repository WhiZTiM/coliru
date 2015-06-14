#include <iostream>
#include <ostream>

struct B
{};

class D1 : /* Private */ B
{
    void g () { std::cout << "D1::g()" << std::endl; }
};

class D2 : protected D1
{};

struct D3 : /* public */ D2
{};

int main()
{
    D1 d1;
    D2 d2;
    D3 d3;
    
    // B& rb1 = d1; // Error: B es innacesible dede D1 (private). 
    // B& rb2 = d2; // Error: B es innacesible desde D2 (protected).
    
    D2& rd2 = d3; // Ok. D2 es accesible desde D3.
    
    // NOTA: Heredar de forma privada significa que tu heredas de forma
    // que nadie lo sepa, y por tanto, no puede haber "casting" desde clases
    // derivadas a bases no públicas, sea cual sea el casting.
    
    // Casting por copia (ni referencia ni puntero):
    // B b = d1; // Error: B es innacesible desde D1.
    
}