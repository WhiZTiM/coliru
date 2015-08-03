#include <iostream>

struct Foo
{
    template <typename T>
    void show(T&& val)
    {
        std::cout << val << ": Universal reference" << std::endl;
    }
    
    template <typename T>
    void show(const T& val)
    {
        std::cout << val << ": const reference" << std::endl;
    }
};

int main()
{
    int value = 1;

    Foo f;
    f.show(value);
    
    const int cvalue = 2;
    f.show(cvalue);
}

