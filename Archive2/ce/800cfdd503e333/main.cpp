#include <type_traits>
#include <functional>

#include <iostream>

struct test
{
    template<class T, typename std::enable_if<std::is_integral<T>::value>::type * = nullptr>
    test(T t) { std::cout << "int"; }
    
    template<class T, typename std::enable_if<!std::is_integral<T>::value>::type * = nullptr>
    test(T t) { std::cout << "not int"; }
};

int main()
{
    test t(5);
    test u("s");
}