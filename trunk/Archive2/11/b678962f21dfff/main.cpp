#include <string>
#include <iostream>
#include <algorithm>

int main()
{
    std::string s = "cool";
    std::for_each(s.begin(), s.end(), [](char& c) { if (c == 'o') c = ''; });
    std::cout << s << std::endl;
    
    return 0;
}