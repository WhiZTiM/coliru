#include <iostream>

int main()
{
    int cap = 24;
    int capid = 3;
    std::cout << "Cap ID: " << (cap == 24 ? "--" : std::to_string(capid)) << std::endl;
}
