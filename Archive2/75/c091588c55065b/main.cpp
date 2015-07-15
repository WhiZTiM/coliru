#include <iostream>
#include <functional>

using namespace std;

template <typename RetType, typename... ArgTypes>
RetType q(function<RetType(ArgTypes...)> f, ArgTypes... args)
{
    return f(args...);
}

int h(int a, int b, int c) { return a + b + c; }

int main()
{
    auto r = q(&h, 1, 2, 3);

    cout << "called, result = " << r;

    return 0;
}