#include <iostream>
#include <string>
#include <utility>
#include <typeinfo>

using namespace std;

//------------------------

template<class T>
struct has_member
{
    bool _value;
    
public:
    
    template<class S>
    constexpr has_member(T S::*)
    : _value( true ) {}
    
    constexpr has_member(...)
    : _value( false ) {}
    
    constexpr operator bool() { return _value; }

    static constexpr bool value = true;

    template<class S, T S::*>
    using check = std::true_type;
};

template<class Result, class... Args>
class has_member<Result( Args... )>
{
    bool _value;
    
public:
    template<class T>
    constexpr has_member(Result (T::*)(Args...))
    : _value( true )
    { }
    
    constexpr has_member(...)
    : _value( false )
    { }
    
    constexpr operator bool()
    { return _value; }
    
    static constexpr bool value = true;

    template<class T, Result (T::*)(Args...)>
    using check = std::true_type;
};

template<class T, template<class> class S>
struct safe_has_member
{
    bool _value;
    
    template<class Q = T>
    static std::true_type check( S<Q>* );
    
    static std::false_type check( ... );
    
public:
    static constexpr bool value = decltype( check( nullptr ) )::value;
};

struct WithFunc
{ void func( int i ); };

struct WrongFunc
{ void func( double i ); };

struct WithoutFunc
{ };

// --

struct WithMem
{ int mem; };

struct WrongMem
{ double mem; };

struct WithoutMem
{ };

template<class T>
using has_func = has_member<void(int)>::check<T, &T::func>;

template<class T>
using has_mem = has_member<int>::check<T, &T::mem>;

static_assert( has_member<void(int)>( &WithFunc::func ), "" );
static_assert( !has_member<void(int)>( &WrongFunc::func ), "" );
static_assert( !safe_has_member<WithoutFunc, has_func>::value, "" );
//static_assert( !has_member<void(int)>( &WithoutFunc::func ), "" ); // compile error: func not defined

static_assert( has_member<int>( &WithMem::mem ), "" );
static_assert( !has_member<int>( &WrongMem::mem ), "" );
static_assert( !safe_has_member<WithoutMem, has_mem>::value, "" );
//static_assert( !has_member<int>( &WithoutMem::mem ), "" ); // compile error: mem not defined

//template<class T, class Result, class... Args>
//using 

struct asdf
{
    decltype( has_member<void(int)>( &WrongFunc::func ) );
};

int main()
{
}






