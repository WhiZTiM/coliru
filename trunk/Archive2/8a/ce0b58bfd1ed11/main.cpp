#include <iostream>
#include <regex>

int main()
{
    const char* input = "-123";
    
    std::regex integer_pattern("(\\+|-)?[[:digit:]]+");
    std::cout << (std::regex_match(input, integer_pattern) ?
        "matches" : "does not match") << std::endl;
    
    //const char* str = R"()";
}