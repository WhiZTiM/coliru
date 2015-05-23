#include <iostream>
#include <type_traits>

struct Foo {
    template <class T>
    std::enable_if_t< !std::is_same< T, bool >::value, T > method() {
        std::cout << "base" << std::endl;
        return T();
    }

    template <class T>
    std::enable_if_t< std::is_same< T, bool >::value, T > method() {
        std::cout << "bool" << std::endl;
        return true;
    }
};

int main()
{
    Foo f;
    f.method<int>();
    f.method<double>();
    f.method<bool>();
}
