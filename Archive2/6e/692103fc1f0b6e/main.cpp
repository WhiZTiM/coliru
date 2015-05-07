#include <iostream>

template<class FT>
struct Method;

template<class ReturnT, class... Args>
struct Method<ReturnT(Args...)> {
    ReturnT operator()(Args...) {
        std::cout << "blah\n";
    }
};

int main() {
    Method<void(int, int)> m;
    m(1, 2);
}