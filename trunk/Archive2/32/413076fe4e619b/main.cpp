#include <cstddef>
#include <vector>
#include <memory>
#include <stdexcept>
#include <utility>
#include <iostream>

typedef size_t Index;
typedef unsigned long Natural;
typedef std::vector<Index> PolyIndex;
typedef const PolyIndex& crPolyIndex;
template<Index N> struct PortIdxType{};

bool operator> (bool, PolyIndex);

template<typename D>
struct base
{
    template<Index N, typename T = D>
    static auto foo() -> decltype(std::declval<T*>() -> getOutput<N>(PolyIndex({})));
};

struct derived
{
    static int getOutput;
};


template<typename T>
void print_type()
{
    std::cout << __PRETTY_FUNCTION__ << "\n";
}

int main()
{
    print_type< decltype(base<derived>::foo<0>()) >();
}