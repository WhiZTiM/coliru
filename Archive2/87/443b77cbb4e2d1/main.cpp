#include <iostream>
#include <iomanip>
#include <limits>
#include <cmath>

template <typename T>
class Foo{
    public:
    template <typename U>
    static size_t bar(){
        static const size_t value = counter++;
        return value;
    }
    private:
    static size_t counter;
};

template <typename T>
size_t Foo<T>::counter = 0;

int main ()
{
    std::cout << Foo<int>::template bar<float>() << '\n';
    std::cout << Foo<int>::template bar<int>() << '\n';
    std::cout << Foo<int>::template bar<float>() << '\n';
    std::cout << Foo<float>::template bar<float>() << '\n';
}