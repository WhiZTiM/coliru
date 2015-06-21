#include <iostream>

template<class T> T sum(T x, T y)
{
    return x + y;
}


int main()
{
    // Remember, characters are actually numbers!
    char c = (char) 1;
    
    std::cout << sum(1, 5)     << std::endl   // T == int    (i32)
              << sum(5.0, 7.2) << std::endl   // T == float  (f32)
              << sum('a', c)   << std::endl;  // T == char   ( i8)
    
    return 0;
}