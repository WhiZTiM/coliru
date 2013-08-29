#include <string>
#include <iostream>

template<class T>
struct NodeBase
{
    T value;
    NodeBase(T &&value)
        : value(std::forward<T>(value)) { }
};

int main() {
    std::string s;
    NodeBase<std::string> n(s);
}