#include <iostream>

template<std::size_t R, std::size_t C>
struct x {};

template<std::size_t R, std::size_t C>
class ctor {
public:
    ctor(const x<R, C>& = x<R, C>()) {}
};

int main() {
    ctor<10, 10> y;
    std::cout << 'x';
}