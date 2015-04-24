#include <iostream>
#include <map>

int main()
{
    std::map<float,float> mymap;
    
    mymap[1.0] = 1.0;
    std::cout << mymap[1.0] << std::endl;
}
