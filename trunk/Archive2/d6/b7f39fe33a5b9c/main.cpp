#include <iostream>

template<class T> T sum(T x, T y)
{
    return x + y;
}


int main()
{
    // Remember, characters are actually numbers!
    char c = (char) 1;
    
    std::cout << "1 + 5 = "       << sum(1, 5)       << "\n\n"   // T == int    (i32)
              << "5.0f + 7.2f = " << sum(5.0f, 7.2f) << "\n\n"   // T == float  (f32)
              << "'a' + 1 = "     << sum('a', c)     << "\n\n";  // T == char   ( i8)
    
    return 0;
}