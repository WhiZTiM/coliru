#include <iostream>
#include <future>

auto duurtlang(){ return 13; }
auto moeite(){ return 37; }
auto zwaarleven(){ return 33; }
 
int main() {
    auto dl = std::async( []{ return duurtlang(); } );
    auto mt = std::async( []{ return moeite(); } );
    auto zl = std::async( []{ return zwaarleven(); } );
    
    std::cout << dl.get() << zl.get() << mt.get() << std::endl;
}