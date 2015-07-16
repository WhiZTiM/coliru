#include <cstring>
#include <iostream>
#include <type_traits>
 
struct D
{
    int a;
    char b;
};
 
int main()
{
    D d1, d2;
    
    memset( &d1, 0, sizeof(d1) );
    memset( &d2, 0xff, sizeof(d2) );
    
    d1.a = d2.a = 42;
    d1.b = d2.b = 'a';
    
    std::cout << std::boolalpha;
    std::cout << std::is_trivially_copyable<D>::value << '\n';
    std::cout << sizeof(D) << '\n';
    
    std::cout << !memcmp( &d1, &d2, sizeof(D) ) << '\n';
}