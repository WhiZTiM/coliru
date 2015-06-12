#include <iostream>
#include <utility>
#include <functional>
#include <vector>
 
int main()
{
    typedef std::vector<int> Vec;
    Vec v = {1, 2, 3, 4, 5};
    
    Vec::iterator it;
    for(it = v.begin(); it != v.end(); ++it)
    {
        if (*it == 3)
            break;
    }
    
    Vec::reverse_iterator rit(it);
    for(; rit != v.rend(); ++rit)
        std::cout << *rit << std::endl;
}
