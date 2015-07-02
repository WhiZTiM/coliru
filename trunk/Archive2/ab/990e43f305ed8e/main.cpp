#include <iostream>
#include <numeric>
#include <iterator>

int main()
{
    int a[] = {10, 20, 30, 40};
    int b[] = {1, 2, 3, 4, 5};

    std::cout << 
        std::accumulate(std::begin(a), std::end(a), 0,
                        [&](int acc, int& a_elem) {
                            auto index = std::distance(a, &a_elem);
                            return acc + a[index] * 2 - b[index + 1];
                        })
        << '\n';
}
