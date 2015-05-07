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

namespace Ocean
{

template<typename T>
struct Fish
{
    struct Fins
    {
        Fins(){}

        int swim(unsigned meters)
        {
            return meters;
        }
    };
    T size;
};

    template class Fish<std::wstring>;


struct Tuna : public Fish<std::wstring>
{
    int color;
};

}


namespace Sky
{

struct Bird
{
    struct Wings
    {
        Wings(){}

        int fly(unsigned meters)
        {
            return meters;
        }
    };
    unsigned size;
};



struct Seagul : public Bird
{
    struct Wings
    {
        Wings(){}

        int fly(unsigned meters)
        {
            return meters + 1;
        }
    };
    int color;
};

}

int main()
{
    Sky::Seagul::Wings w;
    std::cout << w.fly(1) << std::endl;
    
    
    Ocean::Tuna t;
    Ocean::Tuna::Fins f;
    f.swim(1);
    
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    std::cout << words << std::endl;
}
