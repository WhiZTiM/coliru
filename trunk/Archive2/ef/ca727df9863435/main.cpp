#include <iostream>
#include <functional>
#include <memory>

int foo()
{
    return 5;
}

int main(int argc, char* argv[])
{
    auto& v = foo();
}