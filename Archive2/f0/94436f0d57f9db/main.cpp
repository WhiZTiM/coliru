#include <iostream>
#include <string>
#include <vector>

class hi;

class derp
{
    friend class hi;
    struct something{};
}

class hi
{
    void hi(something*);    
}

int main()
{
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    std::cout << words << std::endl;
}
