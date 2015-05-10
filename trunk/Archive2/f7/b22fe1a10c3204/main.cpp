#include <cstdio>
#include <string>
#include <iostream>
#include <vector>

template <typename TYPELIST>
class Cache
{
    public :
    template <typename T>
    void get ( const int &inId ) 
    {
        std::cout << "input " << inId << std::endl ;
    }
} ;

int main ( void )
{
    typedef std::vector<int> CacheAbleTypes ;
    Cache<CacheAbleTypes> myCache ;
    
    myCache.get<std::string>(20) ;

    return 0 ;
}