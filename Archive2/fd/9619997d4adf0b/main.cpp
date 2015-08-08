#include <iostream>
#include <vector>
#include <functional>
#include <type_traits>

template <typename F, typename A,
          typename B = typename std::decay<typename std::result_of<F&(A&)>::type>::type>
std::vector<B> functional_map(F func, std::vector<A> v)
{
    std::vector<B> result(v.size());
    for (int i = 0; i < (int)v.size(); ++i)
    {
        result[i] = func(v[i]);
    }
    return result;
}

int square (int x)
{
    return x*x;
}

int main()
{
    std::vector<int> v = {1,2,3,4,5,6,7,8,9,10};
    std::vector<int> v2 = functional_map(square, v);
    for (int y : v2)
    {
        std::cout << y << " ";
    }
}
