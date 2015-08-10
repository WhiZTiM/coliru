#include <iostream>
#include <tuple>

template <typename T, uint32_t Size>
struct Field2
{
    using type = T;
    static const uint32_t size = Size;
};

template <typename T, typename U>
struct selector;

template <typename T, std::size_t... Is>
struct selector<T, std::index_sequence<Is...>>
{
    using type = std::tuple<typename std::tuple_element<Is, T>::type...>;
};

template <std::size_t N, typename... Ts>
struct remove_last_n
{
    using Indices = std::make_index_sequence<sizeof...(Ts)-N>;  
    using type = typename selector<std::tuple<Ts...>, Indices>::type;
};

template <typename ... Ts>
struct ControlledLayout2 
{    
    static constexpr uint32_t get_size()
    {
        return size_impl<Ts...>();
    }
    
    template <typename X, typename... Xs>
    static constexpr uint32_t size_impl(typename std::enable_if<(sizeof...(Xs) > 0)>::type* = 0)
    {
        return ((X::size) + size_impl<Xs...>());
    }
    
    template <typename X>
    static constexpr uint32_t size_impl()
    {
        return X::size;
    }
    
    template <std::size_t field_number>
    static constexpr uint32_t offset()
    {
        using Tuple = typename remove_last_n<sizeof...(Ts)-field_number, Ts...>::type;
        return offset_impl(Tuple{});
    }
    
    template <typename... Xs>
    static constexpr uint32_t offset_impl(std::tuple<Xs...>)
    {
        return size_impl<Xs...>();
    }
    
    static const uint32_t size = get_size();
};

int main()
{
    using Layout  = ControlledLayout2<Field2<int, 32>,
                                      Field2<char, 1>,
                                      Field2<char, 128>,
                                      Field2<long, 64>
                                      >;
    std::cout << Layout::size << std::endl;
    std::cout << Layout::offset<3>() << std::endl;
}