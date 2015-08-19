#include <iostream>
#include <vector>
#include <string>
#include <type_traits>

template < typename T, typename U > auto mix( const std::vector<T>& a, const std::vector<U>& b )
{
    using common_type = typename std::common_type<T,U>::type ;
    std::vector<common_type> result ;

    auto iter_a = a.begin() ;
    for( auto iter_b = b.begin() ; iter_a != a.end() && iter_b != b.end() ; ++iter_a, ++iter_b )
        result.insert( result.end(), { common_type(*iter_a), common_type(*iter_b) } ) ;

    return result ;
}

auto mix( const std::vector<int>& a, const std::vector<double>& b )
{
    std::vector<int> result ;

    auto iter_a = a.begin() ;
    for( auto iter_b = b.begin() ; iter_a != a.end() && iter_b != b.end() ; ++iter_a, ++iter_b )
        result.insert( result.end(), { int( *iter_a + *iter_b ), int( *iter_a - *iter_b ) } ) ;

    return result ;
}

auto mix( const std::vector<double>& a, const std::vector<int>& b ) { return mix(b,a) ; }

std::string mix( const std::string& a, const std::string& b )
{
    std::string result ;

    auto iter_a = a.begin() ;
    for( auto iter_b = b.begin() ; iter_a != a.end() && iter_b != b.end() ; ++iter_a, ++iter_b )
        result.append( { *iter_a, *iter_b } ) ;

    return result ;
}

std::string mix( const char* a, const char* b ) { return mix( std::string(a), b ) ; }

template < typename T, typename U, typename V >
auto mix( const T& a, const U& b, const V& c ) { return mix( mix(a,b), c ) ; }

int main()
{
   const std::vector<double> a { 0.1, 1.2, 2.3, 3.4, 4.5, 5.6, 7.8 } ;
   const std::vector<int> b { 111, 222, 333, 444, 555, 666, 777, 888, 999 } ;
   const std::vector<char> c { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' } ;

   for( auto v : mix( a, b, c ) ) std::cout << v << ' ' ;
   std::cout << '\n' ;

   std::cout << mix( "hello!", "world!!", ".............." ) << '\n' ;
}
