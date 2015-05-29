#include <iostream>
#include <vector>

struct POD
{
    int x,y,z;
    std::vector<float> v;
};

struct EmptyBase
{ };

struct Weird : EmptyBase
{
    int x,y,z;
    std::vector<float> v;
};
    
// inline init for POD
POD p = 
{
    1, 2, 3,
    { 1.0, 2.0, 3.0},
};

Weird w = 
{
    1, 2, 3,
    { 1.0, 2.0, 3.0 },
};
    

int main(void)
{

}