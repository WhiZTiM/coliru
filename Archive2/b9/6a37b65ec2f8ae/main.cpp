#include<iostream>

template <typename T>
class MyClass
{
    public:
    MyClass()
    {
        std::cout << "Nothing to see here. Just a regular T." << std::endl;
    }
};

template <typename T, int N>
class MyClass<T[N]>
{
    public:
    MyClass()
    {
        std::cout << "Creating MyClass templated on an array of size " << N << std::endl;
    }
};

int main()
{
    MyClass <int> {};
    MyClass <int[10]> {};
    return 0;
}