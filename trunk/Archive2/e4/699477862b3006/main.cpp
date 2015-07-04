#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <cstdlib>
#include <typeinfo>

using uint = uint32_t;

struct X {};

template<typename SK,typename T>
struct Component {
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
        return ComponentCount<SK>::get_counter();
    }

    static uint get_counter()
    {
        static uint counter = 0;
        return counter++;
    }
};

/*
template<typename SK>
class ComponentCount
{
    template<typename CSK,typename CT>
    friend struct Component;
    
private:
    template<typename T>
    static uint next() {
        return counter++;
    }
    
    static uint counter;
};

template<typename SK>
uint ComponentCount<SK>::counter=0;
*/

template<typename SK,typename T>
uint const Component<SK,T>::index(ComponentCount<SK>::template next<T>());

// // //

int main()
{
    uint i0 = Component<X,int>::index;
    uint i1 = Component<X,double>::index;
    uint i2 = Component<X,double>::index;
    uint i3 = Component<X,std::string>::index;
    uint i4 = Component<X,int>::index;
    
    std::cout << i0 << ", " << i1 << ", " << i2 << ", " << i3 << ", " << i4 << std::endl;
    
    return 0;
}