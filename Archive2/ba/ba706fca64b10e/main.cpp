#include <iostream>
#include <vector>
#include <utility>
#include <string>
using namespace std;

class Foo
{
public:
    static const std::vector<std::pair<std::string,std::vector<std::string>>> var;
};

const std::vector<std::pair<std::string,std::vector<std::string>>> Foo::var = 
{ // start of vector
    { "pair1", {"one", "two"}},
    { "pair2", {"three", "four"}},
    { "pair3", {"five", "six"}}
};// end of vector

int main()
{
    for (const auto & p : Foo::var)
    {
        std::cout << p.first << "\t";
        for (const auto & e : p.second)
        {
            std::cout << e << "\t";
        }
        std::cout << std::endl;
    }
    return 0;
} 