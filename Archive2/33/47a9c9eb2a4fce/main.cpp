#include <iostream>

struct a
{
    a& operator=(const char& c)
    {
        std::cout << c << "\n";
        return *this;
    }
};

int main()
{
    a zxc;
    int z = 1000;
    zxc = z;
}