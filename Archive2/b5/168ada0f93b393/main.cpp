#include <iostream>
#include <utility>
#include <tuple>
#include <cstddef>

template <typename... Args>
void F3(Args... args)
{
    using expander = int[];
    (void)expander{ 0, (void(std::cout << args << " "), 0)... };
}

template <typename... Args, typename... Params, std::size_t... Is>
void F2(std::index_sequence<Is...>, Params&&... params)
{
    F3<Args...>(std::forward<Params>(params)..., typename std::tuple_element<sizeof...(Params)+Is, std::tuple<Args...>>::type{}...);
}

template <typename... Args, typename... Params>
void F(Params&&... params)
{
    F2<Args...>(std::make_index_sequence<sizeof...(Args) - sizeof...(Params)>{}
              , std::forward<Params>(params)...);
}

int main()
{
    F<int, char, float, double>(1, 'c');    
    std::cout << std::endl;
    F<int, char, float, double>(); 
}
