#include <iostream>
#include <array>
#include <algorithm>
#include <iterator>

int main()
{
    std::cout << "Enter values:";
    std::vector<int> array(std::istream_iterator<int>(std::cin), {});
    std::cout << "\nThe values in the array are:\n";
    std::copy(begin(array), end(array), std::ostream_iterator<int>(std::cout, " / "));
}