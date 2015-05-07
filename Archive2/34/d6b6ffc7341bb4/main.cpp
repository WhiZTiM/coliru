#include <type_traits>

int main() {
    auto lambda = [](auto&& x) -> decltype(x) { 
        return x;
    };
    
    int i = 7;
    const int ci = 14;
    
    static_assert(std::is_same<decltype(lambda(1)), int&&>::value, "");
    static_assert(std::is_same<decltype(lambda(i)), int&>::value, "");
    static_assert(std::is_same<decltype(lambda(ci)), int const&>::value, "");
}