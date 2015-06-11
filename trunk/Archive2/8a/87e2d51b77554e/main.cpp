#include <list>
#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <algorithm>

enum EnumType 
{
    F = 0,
    M = 10
};

void print(int e)
{
    std::cout << e << std::endl;
}

int main()
{
    print(F);
    int F = 1;
    print(F);
    std::string M = "";
    // print(M); Won't compile
}