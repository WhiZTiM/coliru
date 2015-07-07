#include <iostream>
#include <string>
#include <iomanip>
#include <type_traits>

struct X {
    int i;
    float f;
    std::string str;
};

bool operator< (X const& lhs, X const& rhs) {
    return std::make_tuple(lhs.i, lhs.f, lhs.str) < std::make_tuple(rhs.i, rhs.f, rhs.str);
}
    
int main() { 
    X x1 { 1, 4.3, "foo" };
    X x2 { 2, 6.3, "bar" };
    
    std::cout << std::boolalpha << (x1 < x2) << '\n';
}