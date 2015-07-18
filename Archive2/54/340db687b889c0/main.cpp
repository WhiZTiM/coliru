#include <iostream>
#include <array>
#include <cmath>
#include <utility>
#include <ratio>

template<std::size_t... Indices>
constexpr std::array<double, sizeof...(Indices)> make_grid(
    double a,
    double b,
    std::index_sequence<Indices...>
) 
{
    double h = (b-a)/sizeof...(Indices);
    return {{ (a + Indices*h)... }};
}

template<typename Function, std::size_t... Indices>
constexpr std::array<double, sizeof...(Indices)> make_values(
    Function f,
    const std::array<double, sizeof...(Indices)> grid,
    std::index_sequence<Indices...>) 
{
    return {{ (f(grid[Indices]))... }};
}


template<unsigned N, typename A, typename B, double(*f)(double), double(*dfdx)(double)>
double piecewise_constant(double x)
{
    constexpr static double a = static_cast<double>(A::num) / static_cast<double>(A::den);
    constexpr static double b = static_cast<double>(B::num) / static_cast<double>(B::den);
    //constexpr static double h = (b-a)/N; 
    constexpr static double hInv = N/(b-a);
    constexpr static auto indices = std::make_index_sequence<N>{};
    constexpr static std::array<double, N> grid = make_grid(a, b, indices);
    constexpr static std::array<double, N> values = make_values(f, grid, indices);
    
    int i = static_cast<int>((x - a)*hInv);
    if(i<0 || static_cast<unsigned>(i) >= N)
        return f(x);
    
    return values[i];
}

constexpr double f(double x) {
    return std::sqrt(-2.*std::log(x)/x);
}

constexpr double dfdx(double x) {
    return (std::log(x) - 1.) / (x*std::sqrt(-2.*x*std::log(x)));
}

int main() 
{
    auto g = piecewise_constant<10, std::ratio<1, 128>, std::ratio<127, 128>, f, dfdx>;
    double u = g(0.5);
    
    std::cout << u << std::endl;
}
