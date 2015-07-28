#include <iostream>
#include <typeinfo>
 
struct Foo { };
struct Bar { };

template<typename T> void print_name()
{
    std::cout << typeid(T).name() << std::endl;
}

int main() 
{
    print_name<Foo>();
    print_name<Bar>();
    print_name<unsigned int>();
    print_name<const char*>();
}
