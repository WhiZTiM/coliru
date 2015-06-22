#include <iostream>
#include <vector>
#include <iterator>

template<typename T, std::size_t N>
std::vector<T> arr2vec(T[N] const & a)
{
    std::vector<T> temp{};
    return std::move(temp);
}
    

int main(void)
{
    std::string arr[3] = {"a", "b", "c"};
    auto x = arr2vec(arr);
}