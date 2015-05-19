#include <iostream>

int main(){
    auto const a = 13;
    auto const b = 37;
    auto const f =
        [ x = a ]
        ( auto y )
        { return x + y; };
    
    std::cout << f(b) << std::endl;
}

