#include <iostream>
#include <string>
#include <vector>
#include <array>

std::string CharArrayToString(std::array<char, T> &array)
{
    return std::string(std::begin(array), std::end(array));
}

int main()
{
   std::array<char, 10> test;
   test.fill("Huppelke");
   
   cout << CharArrayToString(&array);
   
   
}
