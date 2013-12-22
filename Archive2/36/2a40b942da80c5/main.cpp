#include <iostream>
#include <string>
#include <vector>

void purr ( char a ) {
    std::cout << "char" << std::endl;
    std::cout << a << std::endl;
}

void purr ( std::string a ) {
    std::cout << "std::string selected" << std::endl;
    std::cout << a << std::endl;
}

struct implicit {
    
    operator std::string () {
        return "purr";
    }
  
    template <typename T>
    operator T () {
        return T(42);
    } 
};

int main() {
    const char* meow = "meow";
    purr(meow);
    purr( implicit() );
    
    // int conversion still works properly
    int convert = implicit{};
    std::cout << "implicit conversion to int:" << std::endl;
    std::cout << convert << std::endl;
    
    std::cout << "implicit conversion to string:" << std::endl;
    std::string arf;
    arf = meow;
    std::cout << arf << std::endl;
    arf = implicit{};
    std::cout << arf << std::endl;
}
