#include <boost/optional.hpp>
#include <iostream>
#include <vector>



struct Options1
{
    // nicely encapsulated, but padding makes it kinda cache-unfriendly
    boost::optional<int64_t> options[8];
};


struct Options2
{   
    // more effient storage but entity cohesion is lost.
    int64_t options_[8];
    bool enabled[8];
};



int main()
{
    std::cout << sizeof(Options1) << std::endl;
    std::cout << sizeof(Options2) << std::endl;
}


// Can there be a solution which is cache-friendly without sacrificing cohesion?
