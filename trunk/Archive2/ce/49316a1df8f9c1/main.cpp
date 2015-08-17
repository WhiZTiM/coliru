#include <iostream>
#include <vector>
#include <cassert>
#include <iostream>

template < typename T > struct ArrayList : private std::vector<T>
{
    using base = std::vector<T> ;
    using base::base ;
    using size_type = typename base::size_type ;
    using base::size ;
    using base::begin ;
    using base::end ;
    // etc. etc.

    typename base::reference operator[] ( size_type pos )
    {
        assert( pos < base::size() ) ;
        return base::at(pos) ; // bound-checked access; may throw std::out_of_range
    }

    typename base::const_reference operator[] ( size_type pos ) const
    {
        assert( pos < base::size() ) ;
        return base::at(pos) ; // bound-checked access; may throw std::out_of_range
    }
};

int main()
{
    ArrayList<int> a { 0, 1, 2, 3, 4, 5 } ;
    const ArrayList<int>& ca = a ;
    assert( a[2] == 2 && ca[3] == 3 ) ;

    for( std::size_t i = 0 ; i < a.size() ; ++i ) a[i] *= i ;

    for( int v : ca ) std::cout << v << ' ' ;
    std::cout << '\n' ;
}
