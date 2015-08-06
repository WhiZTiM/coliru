#include <iostream>
#include <string>
#include <array>
#include <memory>


using handle = void*;


void MyDeleter1(void* ph)
{
    std::cout << *(static_cast<int*>(ph)) << std::endl;
}

void MyDeleter2(void** ph)
{
    std::cout << *(static_cast<int*>(*ph)) << std::endl;
}

using unique_resource1 = std::unique_ptr<handle, decltype(&MyDeleter1)>;
using unique_resource2 = std::unique_ptr<handle, decltype(&MyDeleter2)>;



int main()
{
    int i = 42;
    handle h = &i;
    
    auto ur1 = unique_resource1{ &h, &MyDeleter1};
    auto ur2 = unique_resource2{ &h, &MyDeleter2};
}
