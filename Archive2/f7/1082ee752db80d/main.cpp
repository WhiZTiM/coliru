#include <utility>

class Meter
{
    long double _value;
    
    public:
    
    constexpr explicit Meter(long double value) : _value(::std::move(value)) {}
    constexpr Meter(Meter &&) = default;
    constexpr Meter(Meter &) = default;
    
    friend constexpr auto operator +(Meter const&, Meter const&) -> Meter;
    friend constexpr auto operator *(Meter const&, Meter const&) -> Meter;
};

constexpr auto operator +(Meter const &lhs, Meter const &rhs) -> Meter
{
    return Meter(lhs._value + rhs._value);   
}

constexpr auto operator *(Meter const &lhs, Meter const &rhs) -> Meter
{
    return Meter(lhs._value * rhs._value);   
}

constexpr Meter operator "" _m(long double value)
{
    return Meter(value);
}

int main()
{
    const auto x = 2.0_m;
    const auto y = 5.0_m;
    const auto z = x * y;
}
