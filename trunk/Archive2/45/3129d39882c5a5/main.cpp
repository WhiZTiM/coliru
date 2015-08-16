#include <iostream>
#include <string>

struct Pica
{
    std::string x;
    Pica() : x("9") {}
    Pica(const Pica&) = delete;
    Pica(Pica&&) = default;
    Pica& operator=(const Pica&) = delete;
    Pica& operator=(Pica&&) = default;
};

Pica dura()
{
    Pica blz;
    return blz; // ou return Pica();
}

int main()
{
    Pica mama = dura();
    mama = dura();
}
