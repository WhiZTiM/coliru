#include <iostream>

auto s = [] (auto x) {
    return [=] (auto y) {
        return [=] (auto z) {
            return x(z)(y(z));
        };
    };
};

auto k = [] (auto x) {
    return [=] (auto) {
        return x;
    };
};

auto u = [] (auto f) {
    return f(s)(k);
};

int main() {
    std::cout << u(u(u(u)))(1)(2) << '\n';
}