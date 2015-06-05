#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
#include <iterator>

struct client { client( /* ... */ ) { /* ... */ }  /* ... */ };

int main()
{
    std::vector< std::unique_ptr<client> > clients ;
    for( int i = 0 ; i < 10 ; ++i ) clients.push_back( std::make_unique<client>( /* ... */ ) ) ;

    for( int i = 0 ; i < 10 ; i += 2 ) clients[i] = nullptr ;
    for( const auto& ptr : clients )
        if(ptr) std::cout << ptr.get() << ' ' ; else std::cout << "<nullptr> " ;

    clients.erase( std::remove( std::begin(clients), std::end(clients), nullptr ), std::end(clients) ) ;
    std::cout << "\n\nafter erase-remove: " ;
    for( const auto& ptr : clients )
        if(ptr) std::cout << ptr.get() << ' ' ; else std::cout << "nullptr " ;
    std::cout << '\n' ;
}
