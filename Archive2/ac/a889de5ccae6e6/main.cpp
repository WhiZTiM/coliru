#include <iostream>

template <typename Type>
class SomeClass {
    Type p;
public:
    SomeClass(Type x) { p = x; }
    template <typename Type2>
        SomeClass(SomeClass<Type2> k) { p = k.GetP(); }
    Type GetP() { return p; }
};

int main()
{
    SomeClass<double> c(2.4);
    SomeClass<int> c1(c);
    std::cout << c1.GetP() << std::endl;

    return 0;
}