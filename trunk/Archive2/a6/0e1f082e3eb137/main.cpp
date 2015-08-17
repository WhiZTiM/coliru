#include <regex>
#include <iostream>

int main() {
    std::regex pattern("src/(.*)\.cpp");
    if(std::regex_match("test.h", pattern)) {
        std::cout << "matched" << std::endl;
    }
    else {
        std::cout << "no match" << std::endl;
    }

    return 0;
}