#include <iostream>
#include <string>
#include <vector>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

void* c = NULL;

int main()
{
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    
    std::cout << words << std::endl;
    
    
    void* a = NULL;
    
    void** b;
    b = &a;
    
    c=&b;

    std::cout << &c << std::endl;
    
    a = (void*)4;
    
    std::cout << &c << std::endl;
    
}
