//test.cpp
#include <iostream>
#include <vector>
#include <type_traits>
#include <functional>
#include <memory>

struct Type
{
    int boop;
};

int main()
{
    std::unique_ptr<void, void(*)(void*)>(new Type{}, [](void* ptr){ delete static_cast<Type*>(ptr); });
    return 0;
}
