#include <iostream>

enum class Colours : char
{ 
    RED = 0x66, 
    GREEN = 0x61, 
    BLUE = 0x67, 
};

void WhatIsMyColour(Colours colour)
{
     switch ( colour )
    {
        case Colours::RED:
        case Colours::GREEN:
        case Colours::BLUE:
            std::cout << (char)colour << std::endl;
            break;
        default:
            std::cout << "s" << std::endl;
            break;
    }   
}

int main()
{
    WhatIsMyColour( Colours::RED );
    WhatIsMyColour( Colours::GREEN );
    WhatIsMyColour( Colours::BLUE );
    WhatIsMyColour( (Colours) 100000 );
}
