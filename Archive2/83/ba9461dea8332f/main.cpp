#include <iostream>
#include <algorithm>
#include <initializer_list>

template < std::size_t N > struct arithmetic_t
{
    arithmetic_t() = default ;

    arithmetic_t( const bool (&w1)[N], const bool (&w2)[N] )
    {
        // http://en.cppreference.com/w/cpp/algorithm/copy
        std::copy( w1, w1+N, word1 ) ;
        std::copy( w2, w2+N, word2 ) ;
    }

    // http://en.cppreference.com/w/cpp/utility/initializer_list
    template < typename T > arithmetic_t( std::initializer_list<T> il_one,
                                          std::initializer_list<T> il_two )
    {
        // http://en.cppreference.com/w/cpp/algorithm/min
        auto sz = std::min( il_one.size(), N ) ;
        std::copy( il_one.begin(), il_one.begin()+sz, word1 ) ;

        sz = std::min( il_two.size(), N ) ;
        std::copy( il_two.begin(), il_two.begin()+sz, word2 ) ;
    }

    arithmetic_t& operator &= ( const arithmetic_t& that )
    {
        for( std::size_t i = 0 ; i < N ; ++i )
        {
            word1[i] &= that.word1[i] ;
            word2[i] &= that.word2[i] ;
        }
        return *this ;
    }

    bool word1[N] { false };
    bool word2[N] { false };
};

// See: Canonical implementations: Binary arithmetic operators
// in: http://en.cppreference.com/w/cpp/language/operators
template < std::size_t N >
arithmetic_t<N> operator& ( arithmetic_t<N> a, const arithmetic_t<N>& b )
{ return a &= b ; }

template < std::size_t N >
std::ostream& operator << ( std::ostream& stm, const arithmetic_t<N>& a )
{
    stm << '{' ;
    for( bool v : a.word1 ) stm << v ;
    stm << ',' ;
    for( bool v : a.word2 ) stm << v ;
    return stm << '}' ;
}

int main()
{
    using arithmetic = arithmetic_t<8> ;

    arithmetic a ;
    std::cout << "    a: " << a << '\n' ;

    bool array1[] = {1,0,1,1,1,0,1,1};
    bool array2[] = {1,1,1,0,0,1,1,0};
    arithmetic b( array1, array2 ) ;
    std::cout << "    b: " << b << '\n' ;

    arithmetic c ( {1,1,1,1,0,0,0,0}, {0,0,0,0,1,1,1,1} ) ;
    std::cout << "    c: " << c << '\n' ;

    std::cout << "b & c: " << (b&c) << '\n' ;
}
