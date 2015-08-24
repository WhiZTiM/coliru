#include <iostream>
#include <iomanip>
#include <limits>

int main()
{
    std::cout << std::fixed << std::setprecision(2) << std::showpos ;

    int i = std::numeric_limits<int>::max() ;
    std::cout << "int: " << i << "   int=>float: " << float(i)
              <<  "   int=>float=>int: " << int( float(i) ) << '\n'
              << "int: " << i << "  int=>double: " << double(i)
              << "  int=>double=>int: "  << int( double(i) ) << "\n\n" ;

    i = std::numeric_limits<int>::min() ;
    std::cout << "int: " << i << "   int=>float: " << float(i)
              <<  "   int=>float=>int: " << int( float(i) ) << '\n'
              << "int: " << i << "  int=>double: " << double(i)
              << "  int=>double=>int: "  << int( double(i) ) << "\n\n" ;

    long long ll = std::numeric_limits<long long>::max() ;
    std::cout << "long long: " << ll << "   long long=>float: " << float(ll)
              <<  "    long long=>float=>long long: " << (long long)( float(ll) ) << '\n'
              << "long long: " << ll << "  long long=>double: " << double(ll)
              << "   long long=>double=>long long: "  << (long long)( double(ll) ) << "\n\n" ;

    ll = std::numeric_limits<long long>::min() ;
    std::cout << "long long: " << ll << "   long long=>float: " << float(ll)
              <<  "    long long=>float=>long long: " << (long long)( float(ll) ) << '\n'
              << "long long: " << ll << "  long long=>double: " << double(ll)
              << "   long long=>double=>long long: "  << (long long)( double(ll) ) << "\n\n" ;
}
