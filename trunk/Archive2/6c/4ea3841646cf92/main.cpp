#include <iostream>
#include <utility>

std::uint64_t arr1[8] = {1, 7, 2, 4, 8, 9, 3, 6};
std::uint64_t arr2[8] = {1, 7, 2, 4, 8, 9, 3, 6};
std::uint64_t arr3[8] = {1, 7, 2, 5, 8, 9, 3, 6};
std::uint64_t arr4[8] = {1, 7, 2, 3, 8, 9, 3, 6};

struct less_t
{
    template < typename T, std::size_t N, std::size_t... I >
    bool impl(T const (& lhs)[N], T const (& rhs)[N], std::index_sequence < I... >) const
    {
        bool less = false, done = false;
        ( ( done = done || ( lhs[I] != rhs[I] && ( less = lhs[I] < rhs[I], true ) ) ), ... );
        return less;
    }

    template < typename T, std::size_t N >
    bool operator () (T const (& lhs)[N], T const (& rhs)[N]) const
    {
        return impl(lhs, rhs, std::make_index_sequence < N >());
    }
};

int main()
{
    std::cout << "=== less ===" << std::endl;
    less_t const less{};
    std::cout << less(arr1, arr2) << std::endl;
    std::cout << less(arr1, arr3) << std::endl;
    std::cout << less(arr1, arr4) << std::endl;

    std::cout << less(arr2, arr1) << std::endl;
    std::cout << less(arr2, arr3) << std::endl;
    std::cout << less(arr2, arr4) << std::endl;

    std::cout << less(arr3, arr1) << std::endl;
    std::cout << less(arr3, arr2) << std::endl;
    std::cout << less(arr3, arr4) << std::endl;

    std::cout << less(arr4, arr1) << std::endl;
    std::cout << less(arr4, arr2) << std::endl;
    std::cout << less(arr4, arr3) << std::endl;
}
