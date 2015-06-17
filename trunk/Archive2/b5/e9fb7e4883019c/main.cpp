#include<iostream>
#include<type_traits>

template<typename T, typename U, typename std::enable_if<std::is_convertible<T, U>::value || std::is_base_of<T, U>::value>::type* = nullptr>
T mystatic_cast(U &u)
{
    return u;
}

struct Foo {

};

struct Bar : public Foo {

};

int main() {
    double a = 1.0;
    int    i = mystatic_cast<int>(a);
    std::cout << i << std::endl;
    Bar b;
    Foo f = mystatic_cast<Foo>(b);
    (void) f;
}