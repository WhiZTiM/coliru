#include <iostream>
#include <type_traits>

template <typename T>
class MyClass
{
public:
    template <typename C
            , typename = std::enable_if_t<std::is_class<C>::value>>
    MyClass(C) { std::cout << "class\n"; }
    
    template <typename C
            , typename = std::enable_if_t<std::is_pointer<C>::value>
            , typename = void>
    //        ~~~~~~~~~~~~~~^
    MyClass(C) { std::cout << "pointer\n"; }
};

struct S {};

int main()
{
    int i{};
    MyClass<int> a{ &i };
    MyClass<int> b{ S{} };
}
