#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <cstdlib>
#include <typeinfo>

using uint = uint32_t;

struct SceneKey {
    static uint const max_component_types{8};
};

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
    static uint next()
    {
        uint c = counter;
        counter++;
        
        std::cout << "Registered Component " << c << ": " << typeid(T).name() << std::endl;
        //std::cout << "Registered Component " << std::endl;
        return c;
    }
    
    static uint counter;
};

template<typename SK>
uint ComponentCount<SK>::counter = 0;

template<typename SK,typename T>
uint const Component<SK,T>::index(ComponentCount<SK>::template next<T>());

// // //

int main()
{
    uint i0 = Component<SceneKey,int>::index;
    uint i1 = Component<SceneKey,double>::index;
    uint i2 = Component<SceneKey,double>::index;
    uint i3 = Component<SceneKey,std::string>::index;
    uint i4 = Component<SceneKey,int>::index;
    
    std::cout << i0 << ", " << i1 << ", " << i2 << ", " << i3 << ", " << i4 << std::endl;
    
    return 0;
}