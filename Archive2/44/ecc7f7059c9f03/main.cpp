#include <tuple>
#include <typeinfo>
#include <iostream>
#include <boost/typeof/typeof.hpp>
#include <boost/type_traits.hpp>

using namespace std;

template <typename R>
struct Terminal {};

template <typename R, typename E1>
struct Unary {};

template <typename R, typename E1, typename E2>
struct Binary {};

template <typename R, int S>
struct Arr {};


// Grab the first template arg
template < typename First, typename... Rest>
struct first_template_arg
{
    typedef First type;
};





template < typename R, int N, template <typename, int> class T1, typename T2>
typename std::common_type<typename first_template_arg<R>::type, T2>::type
operator *(T1<R, N> const &, T2 const &)
{
    return typename std::common_type<typename first_template_arg<R>::type, T2>::type();
}



template < typename... T1Args, template <typename... > class T1, typename T2>
typename std::common_type<typename first_template_arg<T1Args...>::type, T2>::type
operator *(T1<T1Args... > const &, T2 const &)
{
    return typename std::common_type<typename first_template_arg<T1Args...>::type, T2>::type();
}


template < typename T1, typename... T2Args, template <typename... > class T2 >
typename std::common_type<T1, typename first_template_arg<T2Args...>::type>::type
operator *(T1 const &, T2<T2Args... > const &)
{
    return typename std::common_type<T1, typename first_template_arg<T2Args...>::type>::type();
}

template < typename... T1Args, template <typename... > class T1, typename... T2Args, template <typename... > class T2 >
typename std::common_type<typename first_template_arg<T1Args...>::type, typename first_template_arg<T2Args...>::type>::type
operator *(T1<T1Args... > const &, T2<T2Args... > const &)
{
    return typename std::common_type<typename first_template_arg<T1Args...>::type, typename first_template_arg<T2Args...>::type>::type ();
}


//==========================================================

template <typename T>
struct type_unwrapper
{
    template <std::size_t N>
    using param_t = T;
};

template <template <typename...> class C, typename... Ts>
struct type_unwrapper<C<Ts...>>
{
    static constexpr std::size_t type_count = sizeof...(Ts);

    template <std::size_t N>
    using param_t = typename std::tuple_element<N, std::tuple<Ts...>>::type;
};


template <typename T>
T get_return_type(T const&) {}

template <typename... Args, template <typename...> class T>
typename first_template_arg<Args...>::type
get_return_type(T<Args...> const&) {}

template <typename T>
struct return_type
{
    //typedef boost::function_traits< get_return_type(T) >::result_type type;
    typedef typename type_unwrapper<T>::template param_t<0> type;
};



template <typename T, typename U>
struct binary_return_type
{
    typedef typename std::common_type<typename return_type<T>::type, typename return_type<U>::type>::type type;
};


template <typename T, typename U>
typename binary_return_type<T, U>::type
operator *(T const&, U const&)
{
    return typename binary_return_type<T,U>::type();
}




//==========================================================


int main()
{
    std::cout << typeid(Binary<float, float, int>() * 3.0).name() << std::endl;
}
