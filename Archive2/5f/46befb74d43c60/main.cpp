#include <iostream>
#include <iomanip>
#include <ctime>

int main()
{
    std::time_t time = std::time(nullptr);
    const std::tm tm = *std::localtime( std::addressof(time) );
    
    std::cout << "   %T : " << std::put_time( std::addressof(tm), "%T" ) << '\n'; // does not work with MinGW
    std::cout << "   %D : " << std::put_time( std::addressof(tm), "%D" ) << '\n'; // does not work with MinGW
    std::cout << "   %c : " << std::put_time( std::addressof(tm), "%c" ) << '\n'; // fine with MinGW
}
