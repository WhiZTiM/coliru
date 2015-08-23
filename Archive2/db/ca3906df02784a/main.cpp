#include <string>
#include <cctype>
#include <algorithm>
#include <iostream>
 
int main()
{
    std::string s("hello");
    std::transform(s.begin(), s.end(), s.begin(), (int (*)(int))std::toupper);
    std::cout << s;
}