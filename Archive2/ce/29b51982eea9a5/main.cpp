#include <iostream>
#include <vector>
#include <tuple>

struct F
{
    const char * name;
    
    std::vector<std::tuple<const char *, int, int>> things;
    
    
};


static F foo = 
{
    // name
    "foo",
    
    // things
    {
        { "hello", 1, 2 },
    },
    
};



int main()
{

}

