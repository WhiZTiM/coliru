#include <iostream>
#include <typeinfo>
#include <cxxabi.h>

template <typename Base>
struct expr_node
{
    int eval() const
    { return static_cast<const Base *>(this)->eval(); }
};

template <typename Base>
std::ostream&
operator<<(std::ostream& o, const expr_node<Base>& v)
{
    return operator<<(o, static_cast<const Base&>(v));
}

struct leaf : expr_node<leaf>
{
    leaf(int value)
    : value_(value)
    { }

    int eval() const
    { return value_; }

    int value_;
};

std::ostream&
operator<<(std::ostream& o, const leaf& v)
{
    return o << v.value_;
}

template <typename Left, typename Right>
struct mul_op : expr_node<mul_op<Left, Right>>
{
    mul_op(const Left& left, const Right& right)
    : left_(left), right_(right)
    { }

    int eval() const
    { return left_.eval()*right_.eval(); }

    Left left_;
    Right right_;
};

template <typename Left, typename Right>
mul_op<Left, Right>
operator*(const Left& left, const Right& right)
{
    return mul_op<Left, Right>(left, right);
}

template <typename Left, typename Right>
std::ostream&
operator<<(std::ostream& o, const mul_op<Left, Right>& v)
{
    return o << "(" << v.left_ << "*" << v.right_ << ")";
}

int
main()
{
    leaf a { 3 }, b { 2 }, c { 4 }, d { 5 };

    auto expr = a*b*c*d;

    std::cout << expr << " = " << expr.eval() << "\n";

    std::cout << abi::__cxa_demangle(typeid(expr).name(), 0, 0, nullptr) << "\n";
}