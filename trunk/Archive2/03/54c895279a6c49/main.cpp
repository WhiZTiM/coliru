#include <type_traits>
#include <iostream>

template <bool,typename T>
struct enabler
{

};

template <typename T>
struct enabler<true,T>
{
    typedef T type;
};

template <typename T>
typename enabler<std::is_integral<T>::value, void>::type test1(T input)
{
    std::cout << "this is for only integral" << std::endl;
}

int main()
{
    test1(10);
}
