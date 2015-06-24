#include <iostream>

// Function templated by function pointer
template< void(*F)(int) >
void fun( int i )
{
    F(i);
}

void f1( int i )
{
    std::cout << i << std::endl;
}

int main()
{
    using F2 = void(*)( int );
    
    constexpr F2 f2 = f1;
    // constexpr F2 f2 = []( int i ) { std::cout << i << std::endl; };

    fun<f1>( 42 ); // THIS WORKS
    f2( 42 );      // THIS WORKS
    fun<f2>( 42 ); // THIS DOES NOT WORK (COMPILE-TIME ERROR) !!!

    return 0;
}
