#include <iostream>
#include <array>
#include <algorithm>
#include <iterator>

int main()
{
    std::array<int, 5> array;
    std::cout << "Enter 5 values:";
    std::copy(std::istream_iterator<int>(std::cin),
              std::istream_iterator<int>(),
              begin(array));
    std::cout << "\nThe values in the array are:\n";
    std::copy(begin(array), end(array), std::ostream_iterator<int>(std::cout, " "));
}