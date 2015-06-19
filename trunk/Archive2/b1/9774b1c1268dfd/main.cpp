#include <iostream>
#include <typeinfo>
#include <type_traits>
#include <cmath>
#include <cassert>

// for managing dependency of tags
#include <boost/mpl/set.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/insert.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/for_each.hpp>

// Compile Time Derivative library
namespace ctd
{

// this CRPT class restricts the applicability of templated operators
// EBO should kick in to make this zero-cost in size
template <typename T>
struct Expression
{
    const T& cast() const {return static_cast<T const&>(*this);}
};

struct Constant : Expression<Constant>
{
    using tags = boost::mpl::set0<>;

    explicit Constant(double val) : m_val(val) {static_assert( sizeof(Constant) == sizeof(double), "unexpected sizeof(Constant)" );}
    double value() const {return m_val;}
    
    template <typename DerivTag>
    auto deriv() const {return Constant(0);}

    const double m_val;
};

template <typename Tag>
struct IndepVarBase
{
    using tags = boost::mpl::set1< Tag >;

    template <typename DerivTag>
    auto deriv() const
    {
        using zero = std::integral_constant<int,0>;
        using one = std::integral_constant<int,1>;
        return Constant( std::conditional< std::is_same<Tag,DerivTag>::value, one, zero >::type::value );
    }
};

// independet variable in expressions
template <typename Tag>
struct IndepVar : Expression<IndepVar<Tag>>, IndepVarBase<Tag>
{
    explicit IndepVar(double val) : m_val(val) {static_assert( sizeof(IndepVar) == sizeof(double), "unexpected sizeof(IndepVar)" );}
    
    double value() const {return m_val;}
    
    const double m_val;
};

namespace detail
{
    template <typename LHS, typename RHS>
    using join_tags = typename boost::mpl::fold<
          typename LHS::tags,
          typename RHS::tags,
          boost::mpl::insert<boost::mpl::_1,boost::mpl::_2> >::type;
}

// control when and where to do efficient memoization of intermediate results
// to avoid recomputing the values and the derivatives

template <typename LHS, typename RHS>
struct BinaryExpression
{
    using tags = detail::join_tags<LHS,RHS>;
    
    BinaryExpression(LHS lhs, RHS rhs) : m_lhs(lhs), m_rhs(rhs) {}
    BinaryExpression(const Expression<LHS>& lhs, const Expression<RHS>& rhs) : BinaryExpression(lhs.cast(), rhs.cast()) {}
    
    LHS m_lhs;
    RHS m_rhs;
};

    
template <typename LHS, typename RHS>
struct Add : Expression<Add<LHS,RHS>>, BinaryExpression<LHS,RHS>
{
    using BinaryExpression<LHS,RHS>::BinaryExpression;
    
    double value() const {return this->m_lhs.value() + this->m_rhs.value();}
    
    template <typename DerivTag>
    auto deriv() const {return this->m_lhs.template deriv<DerivTag>() + this->m_rhs.template deriv<DerivTag>();}
};

template <typename LHS, typename RHS>
auto operator+ (const Expression<LHS>& lhs, const Expression<RHS>& rhs) {return Add<LHS,RHS>(lhs,rhs);}
template <typename LHS>
auto operator+ (const Expression<LHS>& lhs, double rhs) {return lhs + Constant(rhs);}
template <typename RHS>
auto operator+ (double lhs, const Expression<RHS>& rhs) {return Constant(lhs) + rhs;}

template <typename LHS, typename RHS>
struct Sub : Expression<Sub<LHS,RHS>>, BinaryExpression<LHS,RHS>
{
    using BinaryExpression<LHS,RHS>::BinaryExpression;
    
    double value() const {return this->m_lhs.value() - this->m_rhs.value();}
    
    template <typename DerivTag>
    auto deriv() const {return this->m_lhs.template deriv<DerivTag>() - this->m_rhs.template deriv<DerivTag>();}
};

template <typename LHS, typename RHS>
auto operator- (const Expression<LHS>& lhs, const Expression<RHS>& rhs) {return Sub<LHS,RHS>(lhs,rhs);}
template <typename LHS>
auto operator- (const Expression<LHS>& lhs, double rhs) {return lhs - Constant(rhs);}
template <typename RHS>
auto operator- (double lhs, const Expression<RHS>& rhs) {return Constant(lhs) - rhs;}

template <typename LHS, typename RHS>
struct Mul : Expression<Mul<LHS,RHS>>, BinaryExpression<LHS,RHS>
{
    using BinaryExpression<LHS,RHS>::BinaryExpression;
    
    double value() const {return this->m_lhs.value() * this->m_rhs.value();}
    
    template <typename DerivTag>
    auto deriv() const {return this->m_lhs.template deriv<DerivTag>() * this->m_rhs + 
                               this->m_lhs * this->m_rhs.template deriv<DerivTag>();}
};

template <typename LHS, typename RHS>
auto operator* (const Expression<LHS>& lhs, const Expression<RHS>& rhs) {return Mul<LHS,RHS>(lhs,rhs);}
template <typename LHS>
auto operator* (const Expression<LHS>& lhs, double rhs) {return lhs * Constant(rhs);}
template <typename RHS>
auto operator* (double lhs, const Expression<RHS>& rhs) {return Constant(lhs) * rhs;}

template <typename LHS, typename RHS>
struct Div : Expression<Div<LHS,RHS>>, BinaryExpression<LHS,RHS>
{
    using BinaryExpression<LHS,RHS>::BinaryExpression;
    
    double value() const {return this->m_lhs.value() / this->m_rhs.value();}
    
    template <typename DerivTag>
    auto deriv() const {return   (this->m_lhs.template deriv<DerivTag>() * this->m_rhs - 
                                  this->m_lhs * this->m_rhs.template deriv<DerivTag>())
                               / (this->m_rhs * this->m_rhs); }
};

template <typename LHS, typename RHS>
auto operator/ (const Expression<LHS>& lhs, const Expression<RHS>& rhs) {return Div<LHS,RHS>(lhs,rhs);}
template <typename LHS>
auto operator/ (const Expression<LHS>& lhs, double rhs) {return lhs / Constant(rhs);}
template <typename RHS>
auto operator/ (double lhs, const Expression<RHS>& rhs) {return Constant(lhs) / rhs;}

template <typename Arg, typename Func, typename Deriv>
struct UnaryFunction : Expression<UnaryFunction<Arg, Func, Deriv>>
{
    using tags = typename Arg::tags;

    UnaryFunction(Arg arg, Func func, Deriv deriv) : m_arg(arg), m_func(func), m_deriv(deriv) {}
    double value() const {return m_func( m_arg.value() );}
    
    template <typename DerivTag>
    auto deriv() const {return m_deriv(m_arg) * m_arg.template deriv<DerivTag>();}

    Arg m_arg;
    Func m_func;
    Deriv m_deriv;
};

template <typename Arg, typename Func, typename Deriv>
auto make_unary_function(Arg arg, Func func, Deriv deriv) 
{
    return UnaryFunction<Arg, Func, Deriv>(arg, func, deriv);
}

template <typename Arg> auto exp(Arg arg) 
{
    auto func = [](auto x){using std::exp; return exp(x);};
    return make_unary_function(arg, func, func);
}

template <typename Arg> auto log(Arg arg) 
{
    auto func = [](double x){return std::log(x);};
    auto deriv = [](auto x){return 1/x;};
    return make_unary_function(arg, func, deriv);
}

template <typename Arg> auto pow(Arg arg, double n)
{
    auto func = [n](double x){return std::pow(x, n);};
    auto deriv = [n](auto x){return n * pow(x, n-1);};
    return make_unary_function(arg, func, deriv);
}

template <typename Arg> auto pow(double n, Arg arg)
{
    auto func = [n](double x){return std::pow(n, x);};
    auto deriv = [n](auto x){return std::log(n) * pow(n, x);};
    return make_unary_function(arg, func, deriv);
}

template <typename Arg> auto sin(Arg arg) 
{
    auto func = [](double x){return std::sin(x);};
    auto deriv = [](auto x){return cos(x);};
    return make_unary_function(arg, func, deriv);
}

template <typename Arg> auto cos(Arg arg) 
{
    auto func = [](double x){return std::cos(x);};
    auto deriv = [](auto x){return -1*sin(x);};
    return make_unary_function(arg, func, deriv);
}

template <typename Arg> auto tan(Arg arg) 
{
    auto func = [](double x){return std::tan(x);};
    auto deriv = [](auto x){auto y = tan(x); return 1 + y*y;};
    return make_unary_function(arg, func, deriv);
}

template <typename Arg> auto abs(Arg arg) 
{
    auto func = [](double x){return std::abs(x);};
    auto deriv = [](auto x){return Constant( x.value() > 0 ? 1 : -1 );};
    return make_unary_function(arg, func, deriv);
}

} // namespace ctd

// Run Time Derivative library
namespace adept
{
    // dummy adouble for testing
    struct adouble
    {
        explicit adouble(double val) : m_val(val) {}
        double value() const {return m_val;}
        double m_val;
    };
}

// link from Compile Time Derivative to Run Time Derivative
namespace ctd
{

// use this independent variable to plug into Adept
template <typename Tag>
struct AdeptIndepVar : Expression<AdeptIndepVar<Tag>>, IndepVarBase<Tag>
{
    explicit AdeptIndepVar(const adept::adouble& val) : m_dependency(val) {}
    
    // take care not to accept a temporary
    explicit AdeptIndepVar(adept::adouble&&) = delete;

    double value() const {return m_dependency.value();}
    
    // dependency tracking to the adouble independent variable
    const adept::adouble& m_dependency;
};

namespace detail
{
    template <typename Tag, typename RetrieveTag>
    struct retrieve_t
    {
        static auto apply(const AdeptIndepVar<Tag>&) {return nullptr;}
    };
    template <typename RetrieveTag>
    struct retrieve_t<RetrieveTag,RetrieveTag>
    {
        static auto apply(const AdeptIndepVar<RetrieveTag>& arg) {return &arg.m_dependency;}
    };
    
    // guarantee uniqueness in retrieve
    template <typename T> T* unique_retrieve(T* ptrLHS, T* ptrRHS) 
    {
        if (ptrLHS && ptrRHS)
        {
            // this assert triggers when there is more than one independent variable registered with the same tag
            assert( ptrLHS == ptrRHS );
            return ptrLHS;
        }
        if (ptrLHS) return ptrLHS;
        return ptrRHS;
    }
    template <typename T> T* unique_retrieve(std::nullptr_t, T* ptrRHS) {return ptrRHS;}
    template <typename T> T* unique_retrieve(T* ptrLHS, std::nullptr_t) {return ptrLHS;}
}
    
// make retrieve machinery non-intrusive 
// use overloaded standalone functions instead of a member function
template <typename RetrieveTag>
auto retrieve(const Constant&) {return nullptr;}

template <typename RetrieveTag, typename LHS, typename RHS>
auto retrieve(const BinaryExpression<LHS,RHS>& expr) 
{
     return detail::unique_retrieve( retrieve<RetrieveTag>(expr.m_lhs), retrieve<RetrieveTag>(expr.m_rhs) );
}

template <typename RetrieveTag, typename Arg, typename Func, typename Deriv>
auto retrieve(const UnaryFunction<Arg, Func, Deriv>& f) {return retrieve<RetrieveTag>(f.m_arg);}
    
template <typename RetrieveTag, typename Tag> 
const adept::adouble* retrieve(const AdeptIndepVar<Tag>& arg) 
{
    return detail::retrieve_t<Tag, RetrieveTag>::apply(arg);
}

}

template <typename T>
auto f(T x)
{
    return sin(3*x) + 2 * x;
}

template <typename T>
auto g(T x)
{
    return x * x + pow(x, 3) + pow(3, x);
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
    return 3 + 2 * x * y + exp(y) / x;
}

template <typename F>
double deriv(F func, double x)
{
    // approximate derivative with numeric difference
    const double EPS = 1E-6;
    return (func(x + EPS) - func(x - EPS)) / (2*EPS);
}

template <typename F>
double deriv_second(F func, double x)
{
    // approximate derivative with numeric difference
    const double EPS = 1E-6;
    return (func(x + EPS) + func(x - EPS) - 2*func(x)) / (EPS*EPS);
}

template <typename F>
double deriv_x(F func, double x, double y)
{
    // approximate derivative with numeric difference
    const double EPS = 1E-6;
    return (func(x + EPS, y) - func(x - EPS, y)) / (2*EPS);
}

template <typename F>
double deriv_xx(F func, double x, double y)
{
    // approximate derivative with numeric difference
    const double EPS = 1E-6;
    return (func(x + EPS, y) + func(x - EPS, y) - 2*func(x,y)) / (EPS*EPS);
}

template <typename F>
double deriv_y(F func, double x, double y)
{
    // approximate derivative with numeric difference
    const double EPS = 1E-6;
    return (func(x, y + EPS) - func(x, y - EPS)) / (2*EPS);
}

template <typename F>
double deriv_yy(F func, double x, double y)
{
    // approximate derivative with numeric difference
    const double EPS = 1E-6;
    return (func(x, y + EPS) + func(x, y - EPS) - 2*func(x,y)) / (EPS*EPS);
}

template <typename F>
double deriv_xy(F func, double x, double y)
{
    // approximate derivative with numeric difference
    const double EPS = 1E-6;
    return (deriv_x(func, x, y + EPS) - deriv_x(func, x, y - EPS)) / (2*EPS);
}

template <typename F>
double deriv_yx(F func, double x, double y)
{
    // approximate derivative with numeric difference
    const double EPS = 1E-6;
    return (deriv_y(func, x + EPS, y) - deriv_y(func, x - EPS, y)) / (2*EPS);
}

void test(const double x_in, const double y_in)
{
    using std::cout; using std::endl; using std::cerr;
    {
        struct X {};
        ctd::IndepVar<X> x( x_in );
        
        struct Y {};
        ctd::IndepVar<Y> y( y_in );
        
        auto name_printer = [](auto x) {std::cout << typeid(x).name() << '\n';};
        
        auto r = f(x);
        cout << "r = " << r.value() << " [" << f(x.value()) << "]" << endl;
        cout << "r' = " << r.deriv<X>().value() << " [" << deriv(f<double>, x.value()) << "]" << endl;
        cout << "r'' = " << r.deriv<X>().deriv<X>().value() << " [" << deriv_second(f<double>, x.value()) << "]" << endl;
        cout << "r depends on these tags:\n"; boost::mpl::for_each< decltype(r)::tags >( name_printer );
        cout << endl;
        
        auto w = h(x);
        cout << "w = " << w.value() << " [" << h(x.value()) << "]" << endl;
        cout << "w' = " << w.deriv<X>().value() << " [" << deriv(h<double>, x.value()) << "]" << endl;
        cout << "w'' = " << w.deriv<X>().deriv<X>().value() << " [" << deriv_second(h<double>, x.value()) << "]" << endl;
        cout << "w depends on these tags:\n"; boost::mpl::for_each< decltype(w)::tags >( name_printer );
        cout << endl;
        
        auto z = g_f(x);
        cout << "z = " << z.value() << " [" << g_f(x.value()) << "]" << endl;
        cout << "z' = " << z.deriv<X>().value() << " [" << deriv(g_f<double>, x.value()) << "]" << endl;
        cout << "z'' = " << z.deriv<X>().deriv<X>().value() << " [" << deriv_second(g_f<double>, x.value()) << "]" << endl;
        cout << "z depends on these tags:\n"; boost::mpl::for_each< decltype(z)::tags >( name_printer );
        cout << endl;
        
        auto zz = h_exp(x);
        cout << "zz = " << zz.value() << " [" << h_exp(x.value()) << "]" << endl;
        cout << "zz' = " << zz.deriv<X>().value() << " [" << deriv(h_exp<double>, x.value()) << "]" << endl;
        cout << "zz'' = " << zz.deriv<X>().deriv<X>().value() << " [" << deriv_second(h_exp<double>, x.value()) << "]" << endl;
        cout << "zz depends on these tags:\n"; boost::mpl::for_each< decltype(zz)::tags >( name_printer );
        cout << endl;
    
        auto t = f2(x, y);
        cout << "t = " << t.value() << " [" << f2(x.value(), y.value()) << "]" << endl;
        cout << "dt/dx = " << t.deriv<X>().value() << " [" << deriv_x(f2<double,double>, x.value(), y.value()) << "]" << endl;
        cout << "dt/dy = " << t.deriv<Y>().value() << " [" << deriv_y(f2<double,double>, x.value(), y.value()) << "]" << endl;
        cout << "dt/dxx = " << t.deriv<X>().deriv<X>().value() << " [" << deriv_xx(f2<double,double>, x.value(), y.value()) << "]" << endl;
        cout << "dt/dyy = " << t.deriv<Y>().deriv<Y>().value() << " [" << deriv_yy(f2<double,double>, x.value(), y.value()) << "]" << endl;
        cout << "dt/dxy = " << t.deriv<X>().deriv<Y>().value() << " [" << deriv_xy(f2<double,double>, x.value(), y.value()) << "]" << endl;
        cout << "dt/dyx = " << t.deriv<Y>().deriv<X>().value() << " [" << deriv_yx(f2<double,double>, x.value(), y.value()) << "]" << endl;
        cout << "t depends on these tags:\n"; boost::mpl::for_each< decltype(t)::tags >( name_printer );
        cout << endl;
    }
    
    {
        adept::adouble x( x_in );
        adept::adouble y( y_in );
        
        struct X_tag {};
        struct Y_tag {};
                
        using X = ctd::AdeptIndepVar<X_tag>;
        using Y = ctd::AdeptIndepVar<Y_tag>;
                
        auto z = f2( X(x), Y(y) );
        
        cout << "z = " << z.value() << endl;
        cout << "dz/dx = " << z.deriv<X_tag>().value() << endl;
        cout << "dz/dy = " << z.deriv<Y_tag>().value() << endl;
        boost::mpl::for_each< decltype(z)::tags >( [&z](auto x) {
            cout << "deriv(z) wrt adouble at address [" << ctd::retrieve<decltype(x)>(z) << "] = " << z.deriv<decltype(x)>().value() << endl;} );
        cout << "&x = " << &x << endl;
        cout << "&y = " << &y << endl;
    }
}

int main(int argc, char* argv[])
{
#ifdef ARGV_PARAMS
    if (argc < 3) 
    {
        std::cerr << "Not enough parameters!" << std::endl;
        return -1;
    }
    const double x = std::atof( argv[1] );
    const double y = std::atof( argv[2] );
#elif STDIN_PARAMS
    double x, y;
    std::cout << "Input x:"; std::cin >> x;
    std::cout << "Input y:"; std::cin >> y;
#else
    // compile time params
    const double x = 2.0;
    const double y = 3.5;
#endif
    
    test(x, y);
}
