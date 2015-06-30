#include <cassert> 
#include <iostream>




//
// functors
//
template<typename T>
struct LowerBound
{
    LowerBound(T a) : a(a) {}        
    T operator()(T x) const { return x < a ? a : x; }    
    T a;    
};

template<typename T>
struct UpperBound
{
    UpperBound(T b) : b(b) {}    
    T operator()(T x) const { return b < x ? b : x; }    
    T b;
};


//
// functor factory functions
//
template<typename T>
auto clamp_upper(T b) { return UpperBound<T>{b}; }

template<typename T>
auto clamp_lower(T a) { return LowerBound<T>{a}; }



// 
// enable (LowerBound<T>{a} && UpperBound<T>{b})
//
template<template<class> class LB, template<class> class UB, typename T>
auto operator&& (const LB<T>& lbound, const UB<T>& ubound)
{
    struct Combine
    {
        Combine(const LB<T>& lbound, const UB<T>& ubound) : l(lbound), u(ubound) {}
        T operator()(T t) const
        {
            return l(u(t));
        }
        
        LB<T> l;
        UB<T> u;
        
    };
    return Combine{lbound, ubound};
}



//
// enable (0 < x <= 10) which yields (LowerBound<int>{1} && UpperBound<int>{10})
//
struct X
{
}x;

template<typename T> auto operator<=(X x, T t) { return clamp_upper(t    ); }
template<typename T> auto operator< (X x, T t) { return clamp_upper(t - 1); }

template<typename T> auto operator<=(T t, X x) { return clamp_lower(t    ); }
template<typename T> auto operator< (T t, X x) { return clamp_lower(t - 1); }


template<typename T> auto operator<(LowerBound<T> l, T t) { return l && clamp_upper(t - 1); }
template<typename T> auto operator<(T t, UpperBound<T> rhs) { return clamp_lower(t + 1) && rhs; }

template<typename T> auto operator<=(LowerBound<T> l, T t) { return l && clamp_upper(t); }
template<typename T> auto operator<=(T t, UpperBound<T> rhs) { return clamp_lower(t) && rhs; }
    
    
//
// TEST IT
//
int main()
{   
    assert(((2 <= x) < 4)(1)==2);
    assert(((2 <= x) < 4)(2)==2);
    assert(((2 <= x) < 4)(3)==3);
    assert(((2 <= x) < 4)(4)==3);
    assert(((2 <= x) < 4)(5)==3);
    
    //assert((2 <= (x < 4))(1)==2);
    //assert((2 <= (x < 4))(2)==2);
    //assert((2 <= (x < 4))(3)==3);
    //assert((2 <= (x < 4))(4)==4);
    //assert((2 <= (x < 4))(5)==5);
    
    assert(((2 < x) <= 4)(1)==1);
    assert(((2 < x) <= 4)(2)==2);
    assert(((2 < x) <= 4)(3)==3);
    assert(((2 < x) <= 4)(4)==4);
    assert(((2 < x) <= 4)(5)==4);
    
    //assert((2 < (x <= 4))(1)==2);
    //assert((2 < (x <= 4))(2)==2);
    //assert((2 < (x <= 4))(3)==3);
    //assert((2 < (x <= 4))(4)==4);
    //assert((2 < (x <= 4))(5)==5);
}



