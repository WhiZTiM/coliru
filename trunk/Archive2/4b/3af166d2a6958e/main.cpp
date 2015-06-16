#include <iostream>
#include <tuple>
#include <iomanip>

template <typename T, typename... L>
struct foo{};

template <typename T>
struct bar {
    using toto = T;
};

template <template<typename, typename...> class F, typename T, typename... L>
struct bar<F<T,L...>> {
	using toto = T;
};

int main() {
    
	bar< foo<int,char,char> > a;
}