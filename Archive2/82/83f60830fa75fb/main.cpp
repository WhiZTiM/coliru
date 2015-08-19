#include <iostream>
#include <vector>


template<typename T>
std::vector<std::vector<T>> make_2d_vector(std::size_t rows, std::size_t cols)
{
    return std::vector<std::vector<T>>(rows, std::vector<T>(cols));
}

int main()
{
     auto foo = make_2d_vector<double>(5,10);
     return 0;
}