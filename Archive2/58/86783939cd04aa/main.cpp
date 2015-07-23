#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>

int main()
{
    std::string str = "80,15,2,?,0,71,9,16,?,5,6,7,?,32,5,67,96,?,8,95,100,675,875,0,?,?,?,0,5";
    std::cout << str << '\n' ;

    // avoidable: use <random> instead
    std::srand( std::time(nullptr) ) ;
    const char random_decimal_digit = '0' + std::rand() % 10 ;
    
    std::cout << "replacing all '?' with '" << random_decimal_digit << "'\n" ;
    std::replace( str.begin(), str.end(), '?', random_decimal_digit ) ;
    std::cout << str << '\n' ;
}
