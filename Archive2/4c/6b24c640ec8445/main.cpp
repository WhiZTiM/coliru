#include <type_traits>
#include <iostream>
#include <functional>

#include <map>

int main()
{
    std::map< char, int* > m;
    auto it = m.lower_bound( 'a' );
    if ( it == m.cend() || m.key_comp()( it->first, 'a' ) )
        m.insert( it, { 'a', new int(5000) } );

    
}