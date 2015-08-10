#include <iostream>
#include <tuple>

template <typename T, uint32_t Size>
struct Field2
{
    using type = T;
    static const uint32_t size = Size;
};

template <std::size_t N, typename T, typename... Ts>
struct remove_first_n : remove_first_n<N-1, Ts...>
{
};

template <typename... Ts>
struct remove_first_n<0, Ts...>
{
    using type = std::tuple<Ts...>;
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
        using Tuple = typename remove_first_n<field_number, Ts...>::type;
        return size-offset_impl(Tuple{});
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