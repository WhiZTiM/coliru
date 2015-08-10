#include <iostream>
#include <type_traits>

int main()
{
    float f = 5.0 ;
    float& r = f ;
    const float cf = f ;

    std::cout << std::boolalpha
              << std::is_same< float, decltype(f) >::value << '\n' // true
              << std::is_same< float, decltype(r) >::value << '\n' // false
              << std::is_same< float, typename std::decay< decltype(r) >::type >::value << '\n' // true
              << std::is_same< float, decltype(cf) >::value << '\n' // false
              << std::is_same< float, typename std::decay< decltype(cf) >::type >::value << '\n' ; // true
}
