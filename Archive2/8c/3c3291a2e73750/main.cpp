#include <iostream>

int main() {
    auto append = [](auto &&cnt, auto &&me, auto &&a, auto &&p1, auto &&...p) -> decltype(auto) { 
        if(sizeof...(p) > cnt) 
            return me(++cnt, me, a << p1, p..., 0);
        return a;
    };
    append(0, append, std::cout, 1, 2, 3, 4);
}
