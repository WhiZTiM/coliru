#include <iostream>
#include <vector>

//#define PRINT_FUNCSIG() { std::cout << __FUNCSIG__ << "\n"; }
#define PRINT_FUNCSIG() { std::cout << __PRETTY_FUNCTION__ << "\n"; }

struct loud
{
    loud() PRINT_FUNCSIG()
    loud(loud const&) PRINT_FUNCSIG()
    loud(loud&&) throw() PRINT_FUNCSIG()
};

class StringTokanizer 
{
public:
    template <class Container>
    operator Container ()
    {
        Container container(1);
        return container;
    }
};

int main()
{
    std::vector<loud> tmp = StringTokanizer();
    std::cout << "end\n";
}