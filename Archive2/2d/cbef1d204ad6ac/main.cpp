#include <boost/type_traits.hpp>
#include <typeinfo>
#include <iostream>
#include <complex>

using namespace std;

template < typename R >
class Terminal
{
    
};

template < typename E, typename R >
class Unary
{
    
};

template < typename E1, typename E2, typename R >
class Binary
{
public:
    Binary() {}
    Binary(E1 e1, E2 e2) : e1(e1), e2(e2) {}
    
private:
    E1 e1;
    E2 e2;
};

template < class... Args >
struct select_last;

template < typename T >
struct select_last< T >
{
    typedef T type;
};

template < typename T, typename... Args >
struct select_last< T, Args... >
{
    typedef typename select_last< Args... >::type type;
};

template
    <
        typename... Args1,
        typename... Args2,
        template < typename... > class T1,
        template < typename... > class T2
    >
    Binary
    <
        T1< Args1... >,
        T2< Args2... >,
        typename common_type< typename select_last< Args1... >::type , typename select_last< Args2... >::type >::type
    > const
    operator*(T1< Args1... > u, T2< Args2... > v)
{
    cout << "Operator (expr, expr)" << endl;
    return Binary< T1< Args1... >, T2< Args2... >, typename common_type< typename select_last< Args1... >::type , typename select_last< Args2... >::type >::type >(u, v);
}

template
    <
        typename... Args1,
        template < typename... > class T1,
        typename T2
    >
    Binary
    <
        T1< Args1... >,
        T2,
        typename common_type< typename select_last< Args1... >::type , T2 >::type
    > const
    operator*(T1< Args1... > u, T2 v)
{
    cout << "Operator (expr, value)" << endl;
    return Binary< T1< Args1... >, T2, typename common_type< typename select_last< Args1... >::type , T2 >::type >(u, v);
}

template
    <
        typename... Args2,
        typename T1,
        template < typename... > class T2
    >
    Binary
    <
        T1,
        T2< Args2... >,
        typename common_type< T1 , typename select_last< Args2... >::type >::type
    > const
    operator*(T1 u, T2< Args2... > v)
{
    cout << "Operator (value, expr)" << endl;
    return Binary< T1, T2< Args2... >, typename common_type< T1 , typename select_last< Args2... >::type >::type >(u, v);
}

template < typename... Args, template < typename... > class T>
typename select_last< Args... >::type
eval( T< Args... > )
{
    return typename select_last< Args... >::type();
}

int main()
{
    float f = eval(Binary<int, int, int>() * 2.0);
    double d = eval(2.0f * Binary<int, int, int>());
    int i = eval(Unary<int,int>() * Terminal<int>());
    
    cout << f << " " << d << " " << i << endl;
}
