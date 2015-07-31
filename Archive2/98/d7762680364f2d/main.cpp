#include <iostream>
#include <string>
#include <vector>

int main()
{
    std::vector<std::string> words = {
        "Hello", "from", "GCC"
    };
    
    std::cout << std::distance(decltype(words)::const_iterator(begin(words)), cend(words));
}
