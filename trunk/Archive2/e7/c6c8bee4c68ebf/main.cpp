#include <algorithm>
#include <boost/algorithm/clamp.hpp>
#include <iostream>

template <int A, int B>
struct Rational {
    static constexpr int Top = A;
    static constexpr int Bottom = B;
};

template <typename R1, typename R2>
class NormalizedDouble
{
public:
	NormalizedDouble(double value) : value(clamp(value)) {}
	operator double() { return value; }
private:
	double clamp(double value) { return boost::algorithm::clamp(value, ToDouble<R1>(), ToDouble<R2>()); }
    
    template <typename R>
    constexpr double ToDouble() const
    {
        return (double)R::Top / R::Bottom;
    }
    
	double value;
};
    
int main() {
    
    NormalizedDouble<Rational<1, 2>, Rational<8, 4>> a(0.0);
    std::cout << a << std::endl;
}
