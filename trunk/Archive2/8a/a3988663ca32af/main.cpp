#include <iostream>
#include <string>
#include <regex>

int main()
{
    std::string source = "abcabca";
    std::regex regex("abca");
    
    std::sregex_iterator matches_begin = std::sregex_iterator(source.begin(), source.end(), regex);
    std::sregex_iterator matches_end;
    
    for (std::sregex_iterator it = matches_begin; it != matches_end; ++it) {
        std::smatch match = *it;
        std::cout << "position: " << match.position() << "  match: " << match.str() << std::endl;
    }
}

// Colcusion: it does not find overlapping matches.