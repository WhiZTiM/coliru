#include <random>
#include <iostream>

int main()
{
    char const* names[] =
    {
        "dave", "terrence", "chris", "hugh", "cameron", "dale", "richard", "alex"  
    };
    
    std::random_device r;
    std::uniform_int_distribution<> d(0, sizeof(names) / sizeof(names[0]));
    
    size_t i = d(r);
    
    std::cout << "Your code reviewer is: " << names[i] << '\n';
}