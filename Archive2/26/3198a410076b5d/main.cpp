#include <functional>
#include <memory>
#include <iostream>

int main()
{
    int i = 0;
    std::bind([](int&&){}, std::move(i))();
}