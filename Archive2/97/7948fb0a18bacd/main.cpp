#include <iostream>
#include <string>
#include <vector>


using Words = std::vector<std::string>;


std::ostream& operator<<(std::ostream& os, const Words & words)
{
    for ( auto & word : words)
    {
        os << word << "    ";
    }
    return os;
}


int main()
{
    Words words = { "ffHello", "from", "GCC", __VERSION__, "!" };    
    std::cout << words << std::endl;

}
