#include <iostream>

struct A
{
    int B;
};

struct Snap
{
    template<size_t TSize>
    Snap(const A (&)[TSize])
    {
        std::cout << __PRETTY_FUNCTION__ << '\n';
        // do something with TSize
    }
    
    void A() {}
};

int main()
{
    A pop[] = { {1}, {2}, {3} };
    Snap crackle(pop);
    return 0;
}
