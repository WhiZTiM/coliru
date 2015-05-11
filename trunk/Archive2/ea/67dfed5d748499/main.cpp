#include <iostream>
#include <typeinfo>
#include <type_traits>

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
    double deriv() const {return 0;}
    const double m_val;
};
static_assert( sizeof(Constant) == sizeof(double), "unexpected sizeof(Constant)" );

struct IndepVar : Expression
{
    explicit IndepVar(double val) : m_val(val) {}
    double value() const {return m_val;}
    double deriv() const {return 1;}
    const double m_val;
};
static_assert( sizeof(IndepVar) == sizeof(double), "unexpected sizeof(IndepVar)" );

// how control when and where to do efficient memoization of intermediate results
// to avoid recomputing the values and the derivatives

template <typename LHS, typename RHS>
struct Add : Expression
{
    Add(LHS lhs, RHS rhs) : m_lhs(lhs), m_rhs(rhs) {}
    double value() const {return m_lhs.value() + m_rhs.value();}
    double deriv() const {return m_lhs.deriv() + m_rhs.deriv();}
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
    double deriv() const {return m_lhs.deriv() * m_rhs.value() + m_lhs.value() * m_rhs.deriv();}
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
    double deriv() const {return   (m_lhs.deriv() * m_rhs.value() - m_lhs.value() * m_rhs.deriv()) 
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
auto g_f(T x)
{
    return g( f(x) );
}

template <typename F>
double deriv(F func, double x)
{
    // approximate derivative with numeric difference
    const double EPS = 1E-6;
    return (func(x + EPS) - func(x - EPS)) / (2*EPS);
}

int main()
{
    ctd::IndepVar x(2.0);
    
    auto y = f(x);
    std::cout << "y = " << y.value() << " [" << f(x.value()) << "]" << std::endl;
    std::cout << "y' = " << y.deriv() << " [" << deriv(f<double>, x.value()) << "]" << std::endl;
    
    auto w = h(x);
    std::cout << "w = " << w.value() << " [" << h(x.value()) << "]" << std::endl;
    std::cout << "w' = " << w.deriv() << " [" << deriv(h<double>, x.value()) << "]" << std::endl;
    
    auto z = g_f(x);
    std::cout << "z = " << z.value() << " [" << g_f(x.value()) << "]" << std::endl;
    std::cout << "z' = " << z.deriv() << " [" << deriv(g_f<double>, x.value()) << "]" << std::endl;
    
    return 0;
}
