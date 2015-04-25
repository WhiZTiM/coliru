#include <vector>
#include <iterator>
#include <iostream>

template <typename In, typename OutIt>
void apply(const In&, OutIt ) { }

template <typename In, typename OutIt, typename F, typename... Functors>
void apply(const In& in, OutIt& out, F f, Functors... fs)
{
    *out++ = f(in);
    apply(in, out, fs...);
}

template <typename InIt, typename OutIt, typename... Functors>
void transform(InIt first, InIt last, OutIt d_first, Functors... fs)
{
    while (first != last) {
        apply(*first, d_first, fs...);
        first++;
    }
}

int main() {
    std::vector<int> a{1, 2, 3 ,4, 5};
    std::vector<int> b;
    
    transform(a.begin(), a.end(), std::back_inserter(b), 
        [](int x){ return x; },
        [](int x){ return x*x; });
        
    for (int x : b) {
        std::cout << x << '\n';
    }
}