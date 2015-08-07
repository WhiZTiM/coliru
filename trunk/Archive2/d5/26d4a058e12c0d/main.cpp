#include <iostream>

class Noisy
{
public:
    Noisy()
        { std::cout << "Noisy default construct\n"; }
    Noisy(Noisy const&)
        { std::cout << "Noisy copy\n"; }    
    ~Noisy()
        { std::cout << "Noisy destroy\n"; }
    Noisy& operator=(Noisy const&)
        { std::cout << "Noisy copy assign\n"; return *this; }    
    void swap(Noisy&)
        { std::cout << "Noisy swap\n"; }
};

Noisy foo() {
    Noisy n;
    std::cout << &n << '\n';
    return n;
}

int main()
{
    Noisy* np = new Noisy(foo());
    std::cout << np << '\n';
}