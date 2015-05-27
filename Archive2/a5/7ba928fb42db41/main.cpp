#include <iostream>
#include <string>
#include <vector>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}


template<template<int,bool,char> class>
struct Bar{};

template<int,bool,char> struct Zod{};

template<template<class...> class>
struct Holder{};

template<template<int,bool,char> class A>
struct Holder<A>{};


struct Foo
{
    template<int,bool,char>
    struct inner {};
};

template<typename ... Ts>
struct typelist{};

/*  Problematic code below */
template<typename ... Ts>
struct Baz
{
    template<Ts...>
    struct inner {
        
        
        // compiler complaining that the parameters on inner (which are supposed to be <int,bool,char> ) don't match the parameters of the argument in the Bar<> struct ( which are ALSO supposed to be <int,bool,char>)
        // capture the types to see what actually gets expanded
        
        using captured_types = typelist<Ts...>;
        
    }; // expands into template<int,bool,char> struct inner {};
    
};

template<class T>
class TD;



int main()
{
    Bar<Zod> b_zod;
    Bar<Foo::inner> b_foo;
   // Bar<Baz<int,bool,char>::inner> b_baz; // shouldn't compile
   
   
  // TD<Baz<int,bool,char>::inner<1,false,'f'>::captured_types> captured_td;
   std::cout << "Generated the Bar instantiations!";
}
