#include <algorithm>
#include <iostream>
#include <vector>
#include <set>

int main()
{
    std::vector<int> v = {1, 2, 2, 2, 2, 5, 2, 2, 2, 3, 1, 3};

    std::set<int> s;
    
    for( auto it = v.begin(); it != v.end(); )
    {
        if( s.find(*it) != s.end() )
        {
            it = v.erase(it);
        }
        else
        {
            s.insert(*it);
            ++it;
        }
    }
    
    for(const auto& e : v)
    {
        std::cout << e << ' ';
    }
    std::cout << std::endl;
}
