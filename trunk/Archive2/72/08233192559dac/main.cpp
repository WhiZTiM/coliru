#include <iostream>
#include <type_traits>

template <typename T>
class MyClass
{
public:
    template <typename C>
    MyClass(C&& c) : MyClass(std::forward<C>(c)
                           , std::is_pointer<std::decay_t<C>>{}
                           , std::is_class<std::decay_t<C>>{}) {}
    
private:
    template <typename C>
    MyClass(C&&, std::false_type /*is_pointer*/
               , std::true_type /*is_class*/)
    { std::cout << "class\n"; }
    
    template <typename C>
    MyClass(C&&, std::true_type /*is_pointer*/
               , std::false_type /*is_class*/)
    { std::cout << "pointer\n"; }
};

struct S {};

int main()
{
    int i{};
    MyClass<int> a{ &i };
    MyClass<int> b{ S{} };
}
