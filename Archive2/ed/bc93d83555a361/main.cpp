#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iterator>
#include <functional>

int main()
{
    const std::vector<double> vd { 1.1, 16.16, 2.2, 15.15, 3.3, 14.14, 4.4, 13.13,
                                   9.9, 12.12, 8.8, 11.11, 6.6, 10.10, 5.5, 9.9 } ;

    //    Compute the mean value of the elements in vd; output it
    // double total = std::accumulate( vd.begin(), vd.end(), 0 ); // **** type of literal 0 is int
    const double total = std::accumulate( vd.begin(), vd.end(), 0.0 );
    const double mean = total / vd.size();
    std::cout << "mean == " << mean << '\n';

    //	Make a new vector<double> called vd2 and copy all
    //	elements of vd with values lower than (less than) the mean into vd2.

    // std::vector<double> vd2(vd.size());
    std::vector<double> vd2 ;

    // the result of evaluating a lambda expression is a callable object
    // auto v - polymorphic lambda expression: type of v is deduced when called (C++14)
    const auto less_than_mean = [mean] ( auto v ) { return v < mean ; } ;

    // http://en.cppreference.com/w/cpp/iterator/back_inserter
    std::copy_if( vd.begin(), vd.end(), std::back_inserter(vd2), less_than_mean );
    for( const auto mm : vd2 ) std::cout << mm << ' ';
    std::cout << '\n' ;

    vd2.clear() ;

    // the result of evaluating a bind expression is a callable object
    // std::greater<>::operator() - polymorphic, deduces argument and return types (C++14)
    // http://en.cppreference.com/w/cpp/utility/functional/greater_void
    using std::placeholders::_1 ;
    const auto greater_than_mean = std::bind( std::greater<>(), _1, mean ) ;

    std::copy_if( vd.begin(), vd.end(), std::back_inserter(vd2), greater_than_mean );
    for( const auto mm : vd2 ) std::cout << mm << ' ';
    std::cout << '\n' ;
}
