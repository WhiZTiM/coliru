#include <tuple>
#include <iostream>

struct {
    template<typename First, typename Second>
    constexpr std::pair<First, Second> operator()(First&& first, Second&& second) const
    { return { std::forward<First>(first), std::forward<Second>(second) }; }
} constexpr pair {};

struct {
    template<typename... Args>
    constexpr std::tuple<Args...> operator()(Args&&... args) const
    { return std::tuple<Args...> { std::forward<Args>(args)... }; }
} constexpr tuple {};

template<std::size_t N>
struct get_type {
    template<typename Tuple>
    constexpr auto operator()(Tuple&& tuple) const
    -> decltype( std::get<N>(std::forward<Tuple>(tuple)) )
    { return std::get<N>(std::forward<Tuple>(tuple)); }
};

template<std::size_t N> constexpr get_type<N> get {};

struct {
private:
    template<typename F, typename Tuple, std::size_t... Indices>
    static constexpr auto impl(F&& f, Tuple&& t, std::index_sequence<Indices...>)
    -> decltype( tuple(f(std::get<Indices>(std::forward<Tuple>(t)))...) )
    { return tuple(f(std::get<Indices>(std::forward<Tuple>(t)))...); };
    
public:
    template<typename F, typename Tuple>
    constexpr auto operator()(F&& f, Tuple&& tuple) const
    -> decltype( impl(std::forward<F>(f), std::forward<Tuple>(tuple), std::make_index_sequence<std::tuple_size<std::remove_reference_t<Tuple>>::value> {}) )
    { return impl(std::forward<F>(f), std::forward<Tuple>(tuple), std::make_index_sequence<std::tuple_size<std::remove_reference_t<Tuple>>::value> {}); }
} constexpr apply {};

struct {
    template<typename Tuple>
    constexpr auto operator()(Tuple&& tuple) const
    -> decltype( pair(apply(get<0>, std::forward<Tuple>(tuple)), apply(get<1>, std::forward<Tuple>(tuple))) )
    { return pair(apply(get<0>, std::forward<Tuple>(tuple)), apply(get<1>, std::forward<Tuple>(tuple))); }
} constexpr unzip {};

int main()
{
    auto t = tuple(pair(1, 'A'), pair(2l, "B"), pair(3., "CD"));
    auto p = unzip(std::move(t));
    constexpr auto& _1 = get<0>;
    constexpr auto& _2 = get<1>;
    constexpr auto& _3 = get<2>;
    std::cout << _1(p.first) << '\t' << _2(p.first) << '\t' << _3(p.first) << '\n';
    std::cout << _1(p.second) << '\t' << _2(p.second) << '\t' << _3(p.second) << '\n';
}