#include <iostream>
#include <type_traits>
#include <typeinfo>

template <typename T, typename X, template <class> class comparator>
void compare(const char* text)
{
    auto both = comparator<T>::value == comparator<X>::value;
    std::cout << "They have " << (both ? "the same " : "DIFFERENT ") << text << std::endl;
}

template <typename T, typename X>
void show(T, X)
{
    auto same = std::is_same<typename T::bar, X>::value;
    std::cout << "They are " << (same ? "the same" : "NOT the same") << std::endl;
    
    compare<typename T::bar,X,std::is_const>("const");
    compare<typename T::bar,X,std::is_volatile>("volatile");
    compare<typename T::bar,X,std::is_reference>("references");
    
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