#include <iostream>

struct Foo
{
    template<typename ... Args>
    void bar();
};

namespace detail
{
   template<typename ... Args>
   struct FooHelper
   {
        // Do not instantiate this (why?)
   };
   
   template<typename T1, typename ... Rest>
   struct FooHelper<T1,Rest...>
   {
        static void bar() { std::cout << "Recursive Helper" << std::endl; }   
   };
   
   template<typename T1>
   struct FooHelper<T1>
   {
       static void bar() { std::cout << "Base Helper" << std::endl; }
   };
    
}

template<typename ... Args>
void Foo::bar()
{
    detail::FooHelper<Args...>::bar();
}


struct A {};

int main()
{
    std::cout << "Hello World" << std::endl;
    
    Foo().bar<A>();
    return 0;
}