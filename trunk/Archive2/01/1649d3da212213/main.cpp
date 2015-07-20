#include <algorithm>
#include <iterator>
#include <string>
#include <iostream>
int main()
{
    std::string str = "text.with.some.dots";
    std::cout << "before: " << str << "\n";
 
    std::cout << "after:  ";
    std::string str2;
    std::remove_copy(str.begin(), str.end(),
                     str2.begin(), '.');
    std::cout << "'" << str2 << "'" << '\n';
}