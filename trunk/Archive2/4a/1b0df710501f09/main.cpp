#include <type_traits>
#include <iostream>
#include <functional>

#include <unordered_map>

int main()
{
    std::unordered_map< char, int* > m;
    
    //auto it = m.lower_bound( 'a' );
    //if ( it == m.cend() || m.key_comp()( it->first, 'a' ) )
    //    m.insert( it, { 'a', new int(5000) } );
        
    auto& r = m['a'];
    if(!r)
    {
        std::cout << "need insert";
        r = new int(100500);
    }
   
    for(auto i : m)
        std::cout << *(i.second);
}