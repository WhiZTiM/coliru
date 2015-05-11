#include <iostream>
#include <typeinfo>
#include <type_traits>
#include <cmath>

// Compile Time Derivative
namespace ctd
{

// this class restricts the applicability of templated operators
// EBO should kick in to make this zero-cost in size
struct Expression {};

template <typename LHS, typename RHS, template <typename,typename> class Op>
using enable_expression = 
std::enable_if_t< 
    std::is_base_of<Expression,LHS>::value && 
    std::is_base_of<Expression,RHS>::value,
    Op<LHS,RHS> >;

struct Constant : Expression
{
    Constant(double val) : m_val(val) {}
    double value() const {return m_val;}
    
    template <typename DerivTag>
    double deriv() const {return 0;}
    
    const double m_val;
};
static_assert( sizeof(Constant) == sizeof(double), "unexpected sizeof(Constant)" );

namespace detail
{
    // derivative wrt another variable
    template <typename Tag, typename DerivTag>
    struct deriv
    {
        static double apply() {return 0;}
    };
    
    // derivative wrt the same variable
    template <typename Tag>
    struct deriv<Tag,Tag>
    {
        static double apply() {return 1;}
    };
}

template <typename Tag>
struct IndepVar : Expression
{
    explicit IndepVar(double val) : m_val(val) 
    {
        static_assert( sizeof(IndepVar) == sizeof(double), "unexpected sizeof(IndepVar)" );
    }
    double value() const {return m_val;}
    
    template <typename DerivTag>
    double deriv() const {return detail::deriv<Tag,DerivTag>::apply();}

    const double m_val;
};

// how control when and where to do efficient memoization of intermediate results
// to avoid recomputing the values and the derivatives

template <typename LHS, typename RHS>
struct Add : Expression
{
    Add(LHS lhs, RHS rhs) : m_lhs(lhs), m_rhs(rhs) {}
    double value() const {return m_lhs.value() + m_rhs.value();}
    
    template <typename DerivTag>
    double deriv() const {return m_lhs.deriv<DerivTag>() + m_rhs.deriv<DerivTag>();}
    
    LHS m_lhs;
    RHS m_rhs;
};

template <typename LHS, typename RHS>
enable_expression< LHS, RHS, Add >
operator+ (LHS lhs, RHS rhs) {return Add<LHS,RHS>(lhs,rhs);}

template <typename LHS>
auto operator+ (LHS lhs, double rhs) {return lhs + Constant(rhs);}

template <typename RHS>
auto operator+ (double lhs, RHS rhs) {return Constant(lhs) + rhs;}

template <typename LHS, typename RHS>
struct Mul : Expression
{
    Mul(LHS lhs, RHS rhs) : m_lhs(lhs), m_rhs(rhs) {}
    double value() const {return m_lhs.value() * m_rhs.value();}
    
    template <typename DerivTag>
    double deriv() const {return m_lhs.deriv<DerivTag>() * m_rhs.value() + m_lhs.value() * m_rhs.deriv<DerivTag>();}
    
    LHS m_lhs;
    RHS m_rhs;
};

template <typename LHS, typename RHS>
enable_expression< LHS, RHS, Mul >
operator* (LHS lhs, RHS rhs) {return Mul<LHS,RHS>(lhs,rhs);}

template <typename LHS>
auto operator* (LHS lhs, double rhs) {return lhs * Constant(rhs);}

template <typename RHS>
auto operator* (double lhs, RHS rhs) {return Constant(lhs) * rhs;}

template <typename LHS, typename RHS>
struct Div : Expression
{
    Div(LHS lhs, RHS rhs) : m_lhs(lhs), m_rhs(rhs) {}
    double value() const {return m_lhs.value() / m_rhs.value();}
    
    template <typename DerivTag>
    double deriv() const {return   (m_lhs.deriv<DerivTag>() * m_rhs.value() - m_lhs.value() * m_rhs.deriv<DerivTag>()) 
                                 / (m_rhs.value() * m_rhs.value()) ; }
    LHS m_lhs;
    RHS m_rhs;
};

template <typename LHS, typename RHS>
enable_expression< LHS, RHS, Div >
operator/ (LHS lhs, RHS rhs) {return Div<LHS,RHS>(lhs,rhs);}

template <typename LHS>
auto operator/ (LHS lhs, double rhs) {return lhs * Constant(1/rhs);}

template <typename RHS>
auto operator/ (double lhs, RHS rhs) {return Constant(lhs) / rhs;}

template <typename ARG>
struct Exp : Expression
{
    Exp(ARG arg) : m_arg(arg) {}
    double value() const {return std::exp( m_arg.value() );}
    
    template <typename DerivTag>
    double deriv() const {return value() * m_arg.deriv<DerivTag>();}
    
    ARG m_arg;
};
template <typename ARG> auto exp(ARG arg) {return Exp<ARG>(arg);}

} // namespace ctd

template <typename T>
auto f(T x)
{
    return 3 + 2 * x;
}

template <typename T>
auto g(T x)
{
    return x * x;
}

template <typename T>
auto h(T x)
{
    return 2 / (x*x);
}

template <typename T>
auto h_exp(T x)
{
    return x + exp(x) / (x*x);
}

template <typename T>
auto g_f(T x)
{
    return g( f(x) );
}

template <typename T, typename U>
auto f2(T x, U y)
{
    return 3 + 2 * x + exp(y);
}

template <typename F>
double deriv(F func, double x)
{
    // approximate derivative with numeric difference
    const double EPS = 1E-6;
    return (func(x + EPS) - func(x - EPS)) / (2*EPS);
}

template <typename F>
double deriv_1(F func, double x, double y)
{
    // approximate derivative with numeric difference
    const double EPS = 1E-6;
    return (func(x + EPS, y) - func(x - EPS, y)) / (2*EPS);
}

template <typename F>
double deriv_2(F func, double x, double y)
{
    // approximate derivative with numeric difference
    const double EPS = 1E-6;
    return (func(x, y + EPS) - func(x, y - EPS)) / (2*EPS);
}

int main()
{
    struct X;
    ctd::IndepVar<X> x(2.0);
    
    auto r = f(x);
    std::cout << "r = " << r.value() << " [" << f(x.value()) << "]" << std::endl;
    std::cout << "r' = " << r.deriv<X>() << " [" << deriv(f<double>, x.value()) << "]" << std::endl;
    
    auto w = h(x);
    std::cout << "w = " << w.value() << " [" << h(x.value()) << "]" << std::endl;
    std::cout << "w' = " << w.deriv<X>() << " [" << deriv(h<double>, x.value()) << "]" << std::endl;
    
    auto z = g_f(x);
    std::cout << "z = " << z.value() << " [" << g_f(x.value()) << "]" << std::endl;
    std::cout << "z' = " << z.deriv<X>() << " [" << deriv(g_f<double>, x.value()) << "]" << std::endl;
    
    auto zz = h_exp(x);
    std::cout << "zz = " << zz.value() << " [" << h_exp(x.value()) << "]" << std::endl;
    std::cout << "zz' = " << zz.deriv<X>() << " [" << deriv(h_exp<double>, x.value()) << "]" << std::endl;
    
    struct Y;
    ctd::IndepVar<Y> y(3.5);
    auto z2 = f2(x, y);
    std::cout << "z2 = " << z2.value() << " [" << f2(x.value(), y.value()) << "]" << std::endl;
    std::cout << "dz2/dx = " << z2.deriv<X>() << " [" << deriv_1(f2<double,double>, x.value(), y.value()) << "]" << std::endl;
    std::cout << "dz2/dy = " << z2.deriv<Y>() << " [" << deriv_2(f2<double,double>, x.value(), y.value()) << "]" << std::endl;
    
    return 0;
}
