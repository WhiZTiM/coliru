#include <iostream>
#include <iomanip>
#include <ctime>

int main()
{
    std::time_t time = std::time(nullptr);
    const std::tm tm = *std::localtime( std::addressof(time) );
    
    std::cout << "%T : " << std::put_time( std::addressof(tm), "%T" ) << '\n'; // C++11: does not work with g++ MinGW
    std::cout << "%D : " << std::put_time( std::addressof(tm), "%D" ) << '\n'; // C++11: does not work with g++ MinGW
    std::cout << "%c : " << std::put_time( std::addressof(tm), "%c" ) << '\n'; // classic C++: fine with g++ MinGW
}
