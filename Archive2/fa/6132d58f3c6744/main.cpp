#include <iostream>

static int const arr[4][4] = {
    {1},
    {1,2},
    {1,2,3},
    {1,2,3,4},
};

int main()
{
    for(auto const& r : arr) {
        for(int c : r) {
            std::cout << c << ' ';
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}
