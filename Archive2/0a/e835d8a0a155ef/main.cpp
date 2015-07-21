#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>

int main(int argc, char* argv[])
{
    std::string password = "PassWord";
    size_t upper_case_count = std::count_if( password.cbegin(), password.cend(), std::isupper);
    std::cout << upper_case_count;
}