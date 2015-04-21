#include <iostream>
#include <cstdint>
#include <type_traits>

#define enum_helper(type_name,first,last) type_name operator++(type_name & x) {return x = (type_name)(std::underlying_type<type_name>::type(x) + 1); }\
    type_name operator*(type_name c) {return c;}\
    type_name begin(type_name r) {return type_name:: first;}\
    type_name end(type_name r) {return type_name:: last;}
    
    
    
enum class thingy
{
    a,b,c,d,e,f,g
};
enum_helper(thingy,a,g)

int main()
{
    thingy x;
    for(auto d: x)
    {
        std::cout<<static_cast<int>(d)<<"\n";
    }
}