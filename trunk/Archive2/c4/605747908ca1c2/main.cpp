#include <iostream>
#include <limits>

struct X 
{ 
    static const int i = std::numeric_limits<int32_t>::max(); 
};

int main()
{
    switch(std::numeric_limits<int32_t>::max()) { 
        case std::numeric_limits<int32_t>::max():
            std::cout << "this code works thanks to constexpr\n";
            break;
    }
    return EXIT_SUCCESS;
}
