#include <iostream>
#include <string>
#include <vector>

int main()
{
    std::vector<std::string> words = {
        "Hello", "from", "GCC"
    };
    auto it = begin(words);
    std::advance(it, 1);
    std::cout << std::distance(decltype(words)::const_iterator(it), cend(words));
}
