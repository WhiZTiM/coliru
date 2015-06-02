#include <boost/range/algorithm.hpp>
#include <boost/range/numeric.hpp>
#include <boost/timer/timer.hpp>
#include <iterator>
#include <cstdlib>
#include <vector>

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

int main()
{
    constexpr auto N = 1u << 24;
    vector<Complex> v, u;
    v.reserve(N);
    generate_n(back_inserter(v), N, random_complex);
    u = v;
    boost::random_shuffle(v);
    boost::random_shuffle(u);

    {
        boost::timer::auto_cpu_timer t;
        boost::transform(v, u, v.begin(), [](auto x, auto y) { return x*y; });
    }

    volatile auto anti_opti = boost::accumulate(v, Complex{});
    (void)anti_opti;
}

