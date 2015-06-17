#include <iostream>
#include <utility>

template<typename T>
T &as_lvalue(T &&val) {
    return val;
}

int main(int argc, char** argv)
{
    using TPtr = decltype(&as_lvalue(std::declval<int>()));
    TPtr ptr = nullptr;
}