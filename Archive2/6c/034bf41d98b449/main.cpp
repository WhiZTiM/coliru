#include <iostream>
#include <string>
#include <vector>
#include <array>



template<size_t N>
std::string CharArrayToString(std::array<char, N> &array)
{
    return std::string(std::begin(array), std::end(array));
}

int main()
{
   std::array<char, 10> test;
   test.fill('a');
   
   std::cout << CharArrayToString(test);
   
   
}
