#include <vector>
#include <iostream>

struct foo
{
    foo(int a, int b)
        : a(a), b(b) {}
    int a;
    int b;
};

struct Msg
{
    std::vector<int> valueArray;    
};

template <typename... Args>
Msg func(Args&&... args)
{
    Msg msg;
    std::initializer_list<int>{ 0, (msg.valueArray.push_back(args.a), msg.valueArray.push_back(args.b), 0)... };
    return msg;
}

int main()
{
    Msg msg = func(foo{1,2}, foo{3,4}, foo{5,6});
    
    for (int i : msg.valueArray) std::cout << i << ", ";
}
