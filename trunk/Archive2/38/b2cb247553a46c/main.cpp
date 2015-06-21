#include <iostream>

template<int...>
struct sum;

template<int N, int... Args>
struct sum<N, Args...>
{
    static const int res = N;
};

template<int N, int M, int... Args>
struct sum<N, M, Args...>
{
    static const int res = sum<N + M, Args...>::res;
};

int main()
{
    std::cout << sum<10, 20, 30>::res;
    return 0;
}