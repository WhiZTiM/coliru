#include <string>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <iomanip>
 
int main()
{
    char a[5] = {10, 20, 30, 40, 50};
    std::cout << std::hex << std::setfill('0') << std::setw(2);
    std::copy(a, a+5, std::ostream_iterator<unsigned>(std::cout," "));
}