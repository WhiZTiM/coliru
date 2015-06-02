#include <algorithm>
#include <iterator>
#include <iostream>
#include <numeric>
#include <cstdlib>
#include <vector>
#include <chrono>
using namespace std;

struct Complex
{
    double re = 0., im = 0.;
};

Complex operator+(Complex x, Complex y)
{
    return {x.re + y.re, x.im + y.im};
}

Complex operator*(Complex x, Complex y)
{
    return {x.re*y.re - x.im*y.im, x.re*y.im + x.im*y.re};
}

Complex random_complex()
{
    return {rand() / 1000. - 1000., rand() / 1000. - 1000.};
}

template<typename F>
void benchmark(F f)
{
    using namespace chrono;
    auto start = high_resolution_clock::now();
    f();
    auto end = high_resolution_clock::now();
    auto elapsed = end - start;
    cout << "Elapsed = " << duration_cast<duration<double>>(elapsed).count() << "s" << endl;
}

int main()
{
    constexpr auto N = 1u << 24;
    vector<Complex> v, u;
    v.reserve(N);
    generate_n(back_inserter(v), N, random_complex);
    u = v;
    random_shuffle(begin(v), end(v));
    random_shuffle(begin(u), end(u));

    benchmark([&]
    {
        transform(begin(v), end(v), begin(u), begin(v), [](auto x, auto y) { return x*y; });
    });

    volatile auto anti_opti = accumulate(begin(v), end(v), Complex{});
    (void)anti_opti;
}

