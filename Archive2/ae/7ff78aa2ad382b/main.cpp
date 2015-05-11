#include <iostream>
#include <string>
#include <vector>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}



struct Test
{
    Test(Test&& t)
    {
        std::cout << "rvalue reference copy constructor is used" << std::endl;
    }
    Test(const Test &t)
    {
        std::cout << "old copy constructor is used" << std::endl;
    }
    Test()
    {
        std::cout << "defaul constructor is used" << std::endl;
    }
};

Test test()
{
    Test t;
    std::cout<<"hehe"<<std::endl;
    return t;
}

Test&& test2()
{
    return std::move(Test());
}

void tryfunc(Test&& t)
{
    Test tm(t);
    std::cout << "rvalue reference tryfunc is used" << std::endl;
}

void tryfunc2(const Test& t)
{
    Test tm(t);
    std::cout << "old tryfunc is used" << std::endl;
}

int main()
{
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    tryfunc(Test());
}
