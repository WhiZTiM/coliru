#include<tuple>
#include<iostream>
#include<type_traits>

    template<typename Tuple>
    void get_impl(size_t i, Tuple const& t, typename std::tuple_size<Tuple>::type) {}

    template<size_t N, typename Tuple, typename = std::enable_if_t<std::tuple_size<Tuple>::value != N> >
    void get_impl(size_t i, Tuple const& t, std::integral_constant<size_t, N>)
    {
        if(i==N)
        {
            std::cout<<std::get<N>(t)<<std::endl;
        }
        else
        {
            get_impl(i, t, std::integral_constant<size_t, N+1>());
        }
    }

    template<typename Tuple>
    void get(size_t i, Tuple const& t)
    {
        get_impl(i, t, std::integral_constant<size_t, 0>());
    }


int main()
{
    auto t = std::make_tuple(1,1.0,"hi");
    get(2,t);
}
    