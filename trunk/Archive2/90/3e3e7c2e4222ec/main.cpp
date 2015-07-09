#include <functional>
#include <cstdio>

int main() {
    auto use_int = [](int i) {printf("i = %d\n",i);};
    auto fwd = [](auto f,int k) { f(k); };
    auto f1 [[gnu::unused]] = std::bind(use_int, std::placeholders::_1);
    auto f2 = std::bind(fwd,use_int, std::placeholders::_1);
    std::function<void(int)> fn(f2);
    fn(123);
}
