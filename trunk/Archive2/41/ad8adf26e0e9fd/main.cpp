#include <iostream>
#include <array>
#include <cmath>
#include <ratio>
#include <random>
#include <vector>
#include <chrono>

/*
C++11 version of C++14 std::index_sequence and std::make_index_sequence
*/
template<class T> using Invoke = typename T::type;

template<std::size_t...> struct seq{ using type = seq; };

template<class S1, class S2> struct concat;

template<std::size_t... I1, std::size_t... I2>
struct concat<seq<I1...>, seq<I2...>>
  : seq<I1..., (sizeof...(I1)+I2)...>{};

template<class S1, class S2>
using Concat = Invoke<concat<S1, S2>>;

template<std::size_t N> struct gen_seq;
template<std::size_t N> using GenSeq = Invoke<gen_seq<N>>;

template<std::size_t N>
struct gen_seq : Concat<GenSeq<N/2>, GenSeq<N - N/2>>{};

template<> struct gen_seq<0> : seq<>{};
template<> struct gen_seq<1> : seq<0>{};

/*
https://en.wikipedia.org/wiki/Tridiagonal_matrix_algorithm

1 0 0 0 0 . 0 0 0 0     x[0        d0
1 4 1 0 0 . 0 0 0 0     x[1]       d[0]
0 1 4 1 0 . 0 0 0 0     x[2]       d[1]
. . . . . . . . . .  *  .        = .
0 0 0 0 0 . 0 1 4 1     x[N]       d[N-1]
0 0 0 0 0 . 0 0 0 1     x[N+1]     dN
*/
constexpr double cst_c(int i)
{
    return i==0? 0. : 1./(4.-cst_c(i-1));
}

template<std::size_t N>
constexpr double cst_d(int i, double d0, const std::array<double, N> d)
{
    return i==0? d0 : (d[i-1] - cst_d(i-1, d0, d)) / (4. - cst_c(i-1));
}

template<std::size_t N>
constexpr double cst_x(int i, double d0, const std::array<double, N> d, double dN)
{
    return i==N+1? dN : cst_d(i, d0, d) - cst_c(i)*cst_x(i+1, d0, d, dN);
}

template<std::size_t... Indices>
constexpr std::array<double, sizeof...(Indices)> cst_impl(
    double d0, std::array<double, sizeof...(Indices)-2> d, double dN,
    seq<Indices...>) 
{
    return { (cst_x(Indices, d0, d, dN))... };
}

template<std::size_t N>
constexpr std::array<double, N+2> cubic_spline_tridiagonal(double d0, std::array<double, N> d, double dN)
{
    return cst_impl(d0, d, dN, gen_seq<N+2>{});    
}

/*
Main cubic spline code
https://en.wikipedia.org/wiki/Spline_interpolation
*/
template<std::size_t... Indices>
constexpr std::array<double, sizeof...(Indices)> make_grid(
    double a,
    double h,
    seq<Indices...>
)
{
    return { (a + Indices*h)... };
}

template<typename Func, std::size_t... Indices>
constexpr std::array<double, sizeof...(Indices)> apply(
    Func f,
    const std::array<double, sizeof...(Indices)> x,
    seq<Indices...>) 
{
    return { (f(x[Indices]))... };
}

template<std::size_t... Indices>
constexpr std::array<double, sizeof...(Indices)> spline_coeff_rhs(
    const std::array<double, sizeof...(Indices)+2> y,
    seq<Indices...>
) 
{
    return { (3.*(y[Indices+2] - y[Indices]))... };
}

// A & B must be std::ratio
template<int N, typename A, typename B, double(*f)(double), double(*dfdx)(double)>
double precalc_cubic_spline(double x)
{
    static_assert(N >= 1, "N must be at least 1");
    
    constexpr static double a = static_cast<double>(A::num) / static_cast<double>(A::den);
    constexpr static double b = static_cast<double>(B::num) / static_cast<double>(B::den);
    constexpr static double h = (b-a)/N; 
    constexpr static double hRecipr = N/(b-a);
    constexpr static auto grid = make_grid(a, h, gen_seq<N+1>{});
    constexpr static auto y = apply(f, grid, gen_seq<N+1>{});
    
    // find the coefficients
    constexpr static double rhs0 = dfdx(grid[0])*h;
    constexpr static double rhsN = dfdx(grid[N])*h;
    constexpr static auto rhs = spline_coeff_rhs(y, gen_seq<N-1>{});
    constexpr static auto kh = cubic_spline_tridiagonal(rhs0, rhs, rhsN);
    
    int i = (x - a) * hRecipr;
    if(x < a || i >= N)
        return f(x);
    
    double x1 = grid[i];
    double y1 = y[i];
    double y2 = y[i+1];
    double dy = y2 - y1;
    double kh1 = kh[i];
    double kh2 = kh[i+1];
    double t = (x - x1) * hRecipr;
    double s = 1. - t;
    
    return s*y1 + t*y2 + t*s*((kh1 - dy)*s + (dy - kh2)*t);
}

/*
The rest is testing
*/
constexpr double f(double x) {
    return std::sqrt(-2.*std::log(x)/x);
}

constexpr double dfdx(double x) {
    return (std::log(x) - 1.) / (x*std::sqrt(-2.*x*std::log(x)));
}

template<typename TimeT = std::chrono::milliseconds>
struct measure
{
    template<typename F, typename ...Args>
    static typename TimeT::rep execution(F func, Args&&... args)
    {
        auto start = std::chrono::system_clock::now();
        func(std::forward<Args>(args)...);
        auto duration = std::chrono::duration_cast< TimeT> 
                            (std::chrono::system_clock::now() - start);
        return duration.count();
    }
};

int main() 
{
    auto g = precalc_cubic_spline<500, std::ratio<1, 100>, std::ratio<99, 100>, f, dfdx>;
    for(double x : {1e-3, 0.01, 0.02, 0.03, 0.04, 0.05, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 0.95, 0.96, 0.97, 0.98, 0.99, 0.999, 1.})
    {
        double a = f(x);
        double b = g(x);
        std::cout << a << '\t' << b << '\t' << a - b << std::endl;
    }
    
    int sampleSize = 10 * 1000 * 1000;
    std::vector<double> x(sampleSize);
    std::uniform_real_distribution<double> unif;
    std::default_random_engine re;
    for(int i = 0; i < sampleSize; ++i)
        x[i] = unif(re);
        
    std::vector<double> y(sampleSize);
    
    auto lambda1 = [&]() {
        for(int i = 0; i < sampleSize; ++i)
            y[i] = g(x[i]); 
    };
    
    auto lambda2 = [&]() {
        for(int i = 0; i < sampleSize; ++i)
            y[i] = f(x[i]); 
    };
    
    std::cout << measure<>::execution(lambda1) << std::endl;
    std::cout << measure<>::execution(lambda2) << std::endl;
}
