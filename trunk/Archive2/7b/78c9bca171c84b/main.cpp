#include <iostream>
#include <string>
#include <vector>
#include <utility>

class base {
public:
    auto f(){ return 1; }
};    
class c : base
{
    decltype(std::declval<base&>().f()) i;
};


template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

int main()
{
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    std::cout << words << std::endl;
}
