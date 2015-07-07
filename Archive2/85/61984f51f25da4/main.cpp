#include <iostream>
#include <string>

#include <memory>
#include <cmath>
#include <boost/optional.hpp>
#include <boost/noncopyable.hpp>

// ==== ProtoBuf classes

struct ProtoB {
    ProtoB(const std::string& s): id_(s) {}
    
    bool has_id() const { return !id_.empty(); }
    std::string id() const { return id_; }
    
private:
    std::string id_;
};

struct ProtoA {
    ProtoA(boost::optional<int> a, boost::optional<ProtoB> b): a_(a), b_(b) {}
    
    bool has_a() const { return bool(a_); }
    int a() const { return *a_; }
    
    bool has_b() const { return bool(b_); }
    ProtoB b() const { return *b_; }
    
private:
    boost::optional<int> a_;
    boost::optional<ProtoB> b_;
};

// === decoding routine

template<typename ResultT, typename MessageT, typename FieldT>
boost::optional<ResultT> decodeOptional(
    const MessageT& style,
    bool (MessageT::*has)() const,
    FieldT (MessageT::*value)() const,
    ResultT (*decoder)(const FieldT&))
{
    boost::optional<ResultT> r;
    if ((style.*has)())
        r = (*decoder)((style.*value)());
    return r;
}

#define DECODE_OPTIONAL(msg, field, fieldDecoder) decodeOptional(style, &std::remove_reference<decltype(style)>::type::has_##field, &std::remove_reference<decltype(style)>::type::field, fieldDecoder)

template<typename ResultT, typename MessageT>
ResultT decodeValueOr(
    const MessageT& style,
    bool (MessageT::*has)() const,
    ResultT (MessageT::*value)() const,
    ResultT defaultValue)
{
    return (style.*has)() ? (style.*value)() : defaultValue;
}

#define DECODE_VALUE_OR(msg, field, defValue) decodeValueOr(style, &std::remove_reference<decltype(style)>::type::has_##field, &std::remove_reference<decltype(style)>::type::field, defValue)

// ==== user code

struct B {
    std::string id;
};

struct A {
    int a;
    boost::optional<B> b;
};

B decodeB(const ProtoB& style)
{
    return B{ DECODE_VALUE_OR(style, id, std::string()) };
}

A decodeA(const ProtoA& style)
{
    return A{
        DECODE_VALUE_OR(style, a, 0),
        DECODE_OPTIONAL(style, b, decodeB) };
}

int main()
{
    ProtoA pr(42, ProtoB("abc"));
    
    auto a = decodeA(pr);
    
    std::cout << a.a;
    if (a.b)
        std::cout << " true " << a.b->id;
    else
        std::cout << " false";
    
    return 0;
}
