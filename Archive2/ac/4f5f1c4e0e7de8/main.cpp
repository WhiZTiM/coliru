#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <cstdlib>
#include <typeinfo>

using uint = unsigned int;

template<typename SK,typename T>
struct Component
{
    static uint const index;
};

template<typename SK>
class ComponentCount
{
    template<typename CSK,typename CT>
    friend struct Component;

private:
    template<typename T>
    static uint next() {
        static uint index = get_counter();
        return index;
    }

    static uint get_counter()
    {
        static uint counter = 0;
        return counter++;
    }
};

template<typename SK,typename T>
uint const Component<SK,T>::index(ComponentCount<SK>::template next<T>());

// global scope
struct X {};
struct Y {};

int main()
{
    // function scope
    struct Z{};

    uint x0 = Component<X,int>::index;
    uint x1 = Component<X,double>::index;
    uint x2 = Component<X,double>::index;
    uint x3 = Component<X,std::string>::index;
    uint x4 = Component<X,int>::index;
    uint x5 = Component<X,int>::index;

    std::cout << x0 << ", " << x1 << ", " << x2 << ", "
              << x3 << ", " << x4 << ", " << x5 << std::endl;

    uint y0 = Component<Y,int>::index;
    uint y1 = Component<Y,double>::index;
    uint y2 = Component<Y,double>::index;
    uint y3 = Component<Y,std::string>::index;
    uint y4 = Component<Y,int>::index;
    uint y5 = Component<Y,int>::index;

    std::cout << y0 << ", " << y1 << ", " << y2 << ", "
              << y3 << ", " << y4 << ", " << y5 << std::endl;

    uint z0 = Component<Z,int>::index;
    uint z1 = Component<Z,double>::index;
    uint z2 = Component<Z,double>::index;
    uint z3 = Component<Z,std::string>::index;
    uint z4 = Component<Z,int>::index;
    uint z5 = Component<Z,int>::index;

    std::cout << z0 << ", " << z1 << ", " << z2 << ", "
              << z3 << ", " << z4 << ", " << z5 << std::endl;
              
    std::cout << std::endl;

    return 0;
}
