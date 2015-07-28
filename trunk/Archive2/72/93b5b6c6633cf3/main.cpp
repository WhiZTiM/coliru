#include <array>
#include <iostream>
#include <numeric>
#include <vector>

template <template <typename...> class result_container,typename container_type>
result_container<typename container_type::const_iterator>
makeVectorOfIterators(const container_type &container)
{
    result_container<typename container_type::const_iterator> result(container.size());
    std::iota(result.begin(), result.end(), container.begin());
    return result ;
}

int main() {
    std::array<int, 3> arr{{1, 2, 3}};
    for (auto p : makeVectorOfIterators<std::vector>(arr))
        std::cout << *p << '\n';
}