#include <iostream>
#include <array>
#include <algorithm>
#include <iterator>

int main()
{
    std::vector<int> array;
    std::cout << "Enter values:";
    std::copy(std::istream_iterator<int>(std::cin),
              std::istream_iterator<int>(),
              back_inserter(array));
    std::cout << "\nThe values in the array are:\n";
    std::copy(begin(array), end(array), std::ostream_iterator<int>(std::cout, " "));
}