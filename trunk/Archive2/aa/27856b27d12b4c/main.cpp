#include <iostream>

#define FOO(...) do { static thread_local BAR bar(0,##__VA_ARGS__); } while (false)

struct BAR {
    
    template<typename ... Args>
    BAR( Args&&...args ) { std::cout << " NUM_ARGS=\"" << sizeof ... (args) << "\"\n"; }
};
int main() {
    FOO();
}
