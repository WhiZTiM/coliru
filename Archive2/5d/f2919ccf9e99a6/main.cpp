// For std::string
#include <string>

// For std::cout
#include <iostream>

//Create a generalized list instantiation
template <class... F>
struct overload : F... {
    overload(F... f) : F(f)... {}
};      

//Create an specific end-case, where we directly
//inherit the () operator in order to inherit
//multiple () overloads
template <class F>
struct overload : F {
    using F::operator();
};

//template function to create an overload
template <class... F>
auto make_overload(F... f) {
    return overload<F...>(f...);
}

int main() {

    auto f = [](int x,int y) -> int {
        return x+y;
    };
    auto g = [](double x,double y) -> double {
        return x+y;
    };
    auto h = [](std::string x,std::string y) -> std::string {
        return x+y;
    };

    //Ah, but this is a function.
    auto fgh = make_overload(f,g,h);
    
    
    std::cout << static_cast<int>(fgh(1,2)) << std::endl;
    std::cout << static_cast<double>(fgh(1.5,2.5)) << std::endl;
    std::cout << static_cast<std::string>(fgh("bob","larry")) << std::endl;
    
}