#include <iostream>
#include <cstdlib>
#include <string>

class Test
{
    public:
    Test( )
    {
        std::cout << "Test Called!" << std::endl;
    }
};

int main( )
{
    Test( );
    
    return 0;
}