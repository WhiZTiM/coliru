#include <iostream>
#include <initializer_list>

template <typename>
struct X;


template <typename Coll>
void fn(const Coll& coll) {
    
    X<decltype(coll)> x;
    
    for (auto i : coll) {
        std::cout << i << '\n';
    }
}

constexpr auto ilist = {1, 2};

int main() {
    fn(ilist);
}