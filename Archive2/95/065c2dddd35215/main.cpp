#include <iostream>

int fn(int  i) { std::cout <<  "i" << std::endl; return  i; }
int fn(int *i) { std::cout << "*i" << std::endl; return *i; }

int main()
{
    int *i = new int(3);
    {
        int i(fn(i));
        std::cout << i << std::endl;
    }
    delete i;
}