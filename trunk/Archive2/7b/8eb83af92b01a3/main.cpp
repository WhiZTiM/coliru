#include <iostream>
#include <string>
#include <vector>
#include <map>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

typedef std::map<std::string, int> Dictionary;
int main()
{
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    std::cout << words << std::endl;
    
    std::map<Dictionary, int> a, b;
    
    std::cout << "Is a less than b " << ( a<b ) << std::endl;
    
    Dictionary z;
    z["qqq"] = 1;
    
    a[z]=2;
    
    z["eee"] = 2;
    b[z]=3;
    
    std::cout << "Is a less than b " << ( a<b ) << " b less than a " << ( b<a ) << std::endl;
}
