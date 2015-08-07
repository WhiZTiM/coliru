#include <iostream>
#include <cstring>
#include <typeinfo>
#include <set>

static std::set< const void* > ntbs_locations ;

void dump( const std::type_info& ti )
{
    const auto ptr = ti.name() ;
    const void* pv = ptr ;
    if( ntbs_locations.insert(pv).second )
    {
        static int cnt = 0 ;
        std::cout << ++cnt << ". " << ptr << " (NTBS at: " << pv << ")\n" ;
    }
}

int main()
{
    for( int i = 0 ; i < 100 ; ++i )
    {
        dump( typeid( std::strtol ) ) ;
        dump( typeid( std::cin.getloc() ) ) ;
        dump( typeid( std::strncmp ) ) ;
        dump( typeid( std::cout.rdbuf() ) ) ;
        dump( typeid( typeid(int) ) ) ;
    }

    std::cout << "\n#ntbs: " << ntbs_locations.size() << '\n' ;
}
