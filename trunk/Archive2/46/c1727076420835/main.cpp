#include <iostream>

struct Pies
{
    static void daj_glos()
    {
        std::cout << "woof woof\n";
    }
};

struct Kot
{
    static void daj_glos()
    {
        std::cout << "meow meow\n";
    }
};

template <typename R>
struct Hodowca
{
    void tresuj()
    {
        R::daj_glos();
    }
};

int main()
{
    Hodowca<Pies> hodowca_psow;
    Hodowca<Kot> hodowca_kotow;
    
    hodowca_psow.tresuj();
    hodowca_kotow.tresuj();
}
