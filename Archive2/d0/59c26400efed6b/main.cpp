#include <iostream>

namespace A 
{
    namespace B
    {
        enum E : int;
    }
}

using A::B::E;

enum C::E : int { x = 2 };

int main()
{ 
}