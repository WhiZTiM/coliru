#include <iostream>
class Test
{
    int s=9;
    public:
    int get_s()
    {
        return s;
    }
};
int main()
{
    Test s;
    Test& t{s};      // error in C++11 but not in C++14 why???
    std::cout<<t.get_s();
} 