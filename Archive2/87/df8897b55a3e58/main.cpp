#include <iostream>
#include <string>
#include <vector>

template <typename T>
int distance(typename T::const_iterator lhs, typename T::iterator rhs){
    return std::distance(lhs, typename T::const_iterator{rhs});
}

int main()
{
    std::vector<std::string> words = {
        "Hello", "from", "GCC"
    };
    
    std::cout << distance(cbegin(words), end(words));
}
