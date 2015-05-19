#include <iostream>

int main(){
    int const a = 13;
    int const b = 37;
    auto const f =
        [ x = a ]
        ( auto y )
        { return x + y; };
    
    std::cout << f(b) << std::endl;
}

