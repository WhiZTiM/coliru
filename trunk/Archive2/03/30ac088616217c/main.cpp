#include <type_traits>
#include <iostream>

template <typename T, typename U>
struct test;

template <typename T>
struct test<T, std::integral_constant<T*,nullptr>>
{
    void operator()() { std::cout << "nullptr" << std::endl; }
};

template <typename R, typename...ARGs, R(*fn)(ARGs...)>
struct test<R(ARGs...), std::integral_constant<R(*)(ARGs...),fn>>
{
    void operator()() { std::cout << "fnptr" << std::endl; }
};


template <typename T, T*, typename = void>
struct test2;

template <typename T, T* P>
struct test2<T, P, typename std::enable_if<(P==nullptr)>::type>
{
    void operator()() { std::cout << "nullptr" << std::endl; }
};

template <typename T, T* P>
struct test2<T, P, typename std::enable_if<std::is_function<T>::value>::type>
{
    void operator()() { std::cout << "fnptr" << std::endl; }
};

int foo(){return 3;}

int main()
{
    test<int,std::integral_constant<int*,nullptr>> a;
    a();
    test<decltype(foo), std::integral_constant<decltype(&foo), foo>> b;
    b();

    test2<int, nullptr> c;
    c();
    test2<decltype(foo), foo> d;
    d();
}