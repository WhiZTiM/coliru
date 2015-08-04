#include <iostream>
#include <type_traits>
#include <typeinfo>

template <typename T, typename X>
void show(T, X)
{
    auto same = std::is_same<typename T::bar, const X>::value;
    std::cout << "They are " << (same ? "the same" : "NOT the same") << std::endl;
    
    // the same string is always printed both times
    std::cout << typeid(typename T::bar).name() << std::endl;
    std::cout << typeid(X).name() << std::endl;
}

template <typename T>
struct Foo
{
    static constexpr struct E {} nested {};
    using bar = decltype(nested); // They are NOT the same
 //   using bar = E; // They are the same
};

int main()
{
    Foo<int> x;
    show(x, x.nested);
}