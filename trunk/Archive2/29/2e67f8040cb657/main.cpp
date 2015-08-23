#include <iostream>
#include <utility>
#include <tuple>

struct Noisy
{
    Noisy() { std::cout << "Noisy()" << std::endl; }
    Noisy(const Noisy&) { std::cout << "Noisy(const Noisy&)" << std::endl; }
    Noisy(Noisy&&) { std::cout << "Noisy(Noisy&&)" << std::endl; }
    ~Noisy() { std::cout << "~Noisy()" << std::endl; }
    Noisy& operator=(const Noisy&) { std::cout << "operator=(const Noisy&)" << std::endl; return *this; }
    Noisy& operator=(Noisy&&) { std::cout << "operator=(Noisy&&)" << std::endl; return *this; }
};

template <std::size_t... Is, typename... Types>
auto merge_tuple(std::index_sequence<Is...>, std::tuple<Types...>& t)
{
    return std::tuple_cat(std::move(std::get<Is>(t))...);
}

int main()
{
    std::tuple<std::tuple<Noisy>, std::tuple<Noisy>> t;
    
}
