#include <boost/type_traits.hpp>
#include <iostream>
// Note: 'R' is used for return type
template <typename DerivedType, typename R>
struct Base
{ // ...
};

template <typename E1, typename E2, typename R>
struct MultOperation : public Base<MultOperation<E1, E2, R>, R>
{ // ...
    MultOperation(E1, E2){}
};

template <typename T>
struct Terminal : public Base<Terminal<T>, T>
{ // ...
    Terminal(){}
    Terminal(T){}
};

template<class T>
    struct is_some_kind_of_Base {
        typedef char yes;
        typedef struct { char _[2]; } no;
    
        template<class U, class V>
        static yes test(Base<U, V> *);
        static no test(...);
    
        static const bool value = (sizeof(test((T*)0)) == sizeof(yes));
    };

 

// The broken operators:
template <typename T1, typename T2, typename R1, typename R2>
MultOperation<Base<T1, R1>, Base<T2, R2>, typename boost::common_type<R1, R2>::type>
operator*( Base<T1, R1> const& u, Base<T2, R2> const& v)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    return MultOperation<Base<T1, R1>, Base<T2, R2>, typename boost::common_type<R1, R2>::type>(u, v);
}

template <typename T1, typename T2,  typename R2>
typename boost::disable_if<is_some_kind_of_Base<T1>, MultOperation<Terminal<T1>, Base<T2, R2>, typename boost::common_type<T1, R2>::type> >::type
operator*( T1 const& u, Base<T2, R2> const& v)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    return MultOperation<Terminal<T1>, Base<T2, R2>, typename boost::common_type<T1, R2>::type>(Terminal<T1>(u), v);
}

template <typename T1, typename T2, typename R1>
typename boost::disable_if<is_some_kind_of_Base<T2>, MultOperation<Base<T1, R1>, Terminal<T2>, typename boost::common_type<R1, T2>::type> >::type
operator*( Base<T1, R1> const& u, T2 const& v)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    return MultOperation<Base<T1, R1>, Terminal<T2>, typename boost::common_type<R1, T2>::type>(u, Terminal<T2>(v));
}

int main() {
    Terminal<int> t;
    Terminal<long> t2;
    t * t2;
    t * 1;
}
