#include <vector>
#include <string>
#include <iostream>

template <typename... T>
void foo(T... args)
{    
    std::vector<std::string> names{args...};
    
    for (auto el : names)
        std::cout << el << '\n';
}

int main()
{
    foo("lol", "hi", "there");
}
