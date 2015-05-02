#include <iostream>
#include <algorithm>
#include <vector>

struct good
{
    good() = default ;
    good( const good& ) { std::cout << "good::copy constructor\n" ; }
    good( good&& ) noexcept { std::cout << "good::move constructor\n" ; }
    ~good() noexcept = default ;
    good& operator = ( const good& ) { std::cout << "good::copy assignment\n" ; return *this ; }
    good& operator = ( good&& ) noexcept { std::cout << "good::move assignment\n" ; return *this ; }
};

struct bad
{
    bad() = default ;
    bad( const bad& ) { std::cout << "bad::copy constructor\n" ; }
    bad( bad&& ) { std::cout << "bad::move constructor\n" ; }
    ~bad() = default ;
    bad& operator = ( const bad& ) { std::cout << "bad::copy assignment\n" ; return *this ; }
    bad& operator = ( bad&& ) { std::cout << "bad::move assignment\n" ; return *this ; }
};

int main()
{
    {
        std::vector<good> seq(3) ;
        std::cout << "\nvector of good objects\n------------------\n" ;
        seq.resize(1000) ;
    }

    {
        std::vector<bad> seq(3) ;
        std::cout << "\nvector of bad objects\n------------------\n" ;
        seq.resize(1000) ;
    }
}
