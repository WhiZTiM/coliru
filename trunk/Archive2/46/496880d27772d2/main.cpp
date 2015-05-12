#include <iostream>

enum class Colours
{ 
    RED = 1, 
    GREEN = 2, 
    BLUE = 3 
};

typedef std::underlying_type<Colours>::type Colours_t; 

void WhatIsMyColour(Colours_t colour)
{
     switch ( colour )
    {
        case 1:
            std::cout << "Color is red" << std::endl;
            break;
        case 2:
            std::cout << "Color is green" << std::endl;
            break;
        case 3:
            std::cout << "Color is blue" << std::endl;
            break;
        default:
            std::cout << "Color is unknown" << std::endl;
            break;
    }   
}

int main()
{
    WhatIsMyColour( (Colours_t) Colours::BLUE );
    WhatIsMyColour( (Colours_t) Colours::GREEN );
    WhatIsMyColour( (Colours_t) Colours::RED );
    WhatIsMyColour( (Colours_t) 1000 );
}
