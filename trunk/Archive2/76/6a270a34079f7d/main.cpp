#include<tuple>
#include<vector>
#include<iostream>
#include<functional>



template<typename TupleType, typename FunctionType, size_t N, typename = std::enable_if_t<N != std::tuple_size<std::decay_t<TupleType> >::value> >  //SFINAE required
void tuple_caller_impl(TupleType&& t, FunctionType&& f, std::integral_constant<size_t, N>)
{
    --std::get<N>(t); f(t); ++std::get<N>(t);
    ++std::get<N>(t); f(t); --std::get<N>(t);
    
    tuple_caller_impl(std::forward<TupleType>(t), std::forward<FunctionType>(f), std::integral_constant<size_t, N+1>());
}

template<typename TupleType, typename FunctionType>
void tuple_caller_impl(TupleType&& t, FunctionType&& f, std::integral_constant<size_t, std::tuple_size<std::decay_t<TupleType> >::value>)
{
    f(t); // finally call function on the unchanged tuple
          // could also be done by specializing the 0-th call to tuple_caller_impl
}

template<typename TupleType, typename FunctionType>
void tuple_caller(TupleType&& t, FunctionType&& f)
{
    tuple_caller_impl(std::forward<TupleType>(t), std::forward<FunctionType>(f), std::integral_constant<size_t, 0>());
}

int main()
{
    auto f = [](auto const& t) { std::cout<<"call function with ("<<std::get<0>(t)<<","<<std::get<1>(t)<<","<<std::get<2>(t)<<")"<<std::endl; };
    auto t= std::make_tuple(1,5,3);

    tuple_caller(t,f);
}

