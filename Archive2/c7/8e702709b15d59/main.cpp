#include <iostream>

//#define FOO(...) do { static thread_local BAR bar(0,##__VA_ARGS__); } while (false)

// g++ 
// clang++ 

// g++ 
// clang++ 

// g++ error: cannot declare static function inside another function
// clang++ error: function declared in block scope cannot have 'static' storage class
//#define FOO(...) do { static thread_local BAR bar(__VA_ARGS__); } while (false)

// g++ error: cannot declare static function inside another function
// clang++ error: function declared in block scope cannot have 'static' storage class
// clang++ error: 'thread_local' is only allowed on variable declarations
//#define FOO(...) do { static thread_local BAR bar(##__VA_ARGS__); } while (false)

// g++ error: expected primary-expression before ')' token
// clang++  warning: token pasting of ',' and __VA_ARGS__ is a GNU extension [-Wgnu-zero-variadic-macro-arguments]
//#define FOO(...) do { static thread_local BAR bar(#__VA_ARGS__, ##__VA_ARGS__); } while (false)

// g++ error: expected primary-expression before ')' token
// clang++  warning: token pasting of ',' and __VA_ARGS__ is a GNU extension [-Wgnu-zero-variadic-macro-arguments]
#define FOO(...) do { static thread_local BAR bar{#__VA_ARGS__, ##__VA_ARGS__}; } while (false)

struct BAR {
    template<typename ... Args>
    BAR( Args&&...args ) { std::cout << " NUM_ARGS=\"" << sizeof ... (args) << "\"\n"; }
};
int main() {
    FOO();
}
