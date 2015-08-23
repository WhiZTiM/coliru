#include <iostream>
#include <utility>
#include <tuple>
#include <cstddef>
#include <type_traits>

template<class T, bool can_move>
struct wrapper {
    std::add_pointer_t<T> ptr;
    wrapper(T& t) : ptr(std::addressof(t)) {}
    
    using unwrapped_type = std::conditional_t<can_move, 
                                              std::add_rvalue_reference_t<T>,
                                              std::conditional_t<std::is_rvalue_reference<T>{},
                                                                 T,
                                                                 std::add_lvalue_reference_t<T>>>;
    using type = T;
    
    unwrapped_type unwrap() const{
        return std::forward<unwrapped_type>(*ptr);
    }
};

struct Noisy
{
    Noisy() { std::cout << "Noisy()" << std::endl; }
    Noisy(const Noisy&) { std::cout << "Noisy(const Noisy&)" << std::endl; }
    Noisy(Noisy&&) { std::cout << "Noisy(Noisy&&)" << std::endl; }
    ~Noisy() { std::cout << "~Noisy()" << std::endl; }
    Noisy& operator=(const Noisy&) { std::cout << "operator=(const Noisy&)" << std::endl; return *this; }
    Noisy& operator=(Noisy&&) { std::cout << "operator=(Noisy&&)" << std::endl; return *this; }
};

template<class... Wrappers, std::size_t... Is>
auto unwrap_tuple(const std::tuple<Wrappers...>& t, std::index_sequence<Is...>) {
    return std::tuple<typename Wrappers::type...>(std::get<Is>(t).unwrap()...);
}

template<class... Wrappers>
auto unwrap_tuple(const std::tuple<Wrappers...>& t) {
    return unwrap_tuple(t, std::index_sequence_for<Wrappers...>());
}

template<bool can_move, class V, class T>
auto wrap(T& t, char){
    return wrapper<V, can_move>(t);
}
template<class T> struct is_tuple : std::false_type {};
template<class... Ts> struct is_tuple<std::tuple<Ts...>> : std::true_type {};

template<bool can_move, class, class Tuple, class = std::enable_if_t<is_tuple<std::decay_t<Tuple>>{}>>
auto wrap(Tuple& t, int);

template<bool can_move, class Tuple, std::size_t... Is>
auto wrap(Tuple& t, std::index_sequence<Is...>) {
    return std::make_tuple(wrap<can_move, std::tuple_element_t<Is, Tuple>>(std::get<Is>(t), 0)...);
}

template<bool can_move, class V, class Tuple, class>
auto wrap(Tuple& t, int) {
    return wrap<can_move>(t, std::make_index_sequence<std::tuple_size<Tuple>{}>());
}

template<class Tuple>
auto wrap_tuple(Tuple&& t){
    constexpr bool can_move = !std::is_lvalue_reference<Tuple>{};
    return wrap<can_move>(t, std::make_index_sequence<std::tuple_size<std::decay_t<Tuple>>{}>());
}

template <class T>
auto flatten_tuple(T&& t, char) { return std::make_tuple(std::forward<T>(t)); }

template <class T, class = std::enable_if_t<is_tuple<std::decay_t<T>>{}>>
auto flatten_tuple(T&& t, int);

template<class Tuple, std::size_t... Is>
auto flatten_tuple(Tuple&& t, std::index_sequence<Is...>){
    return std::tuple_cat(flatten_tuple(std::get<Is>(std::forward<Tuple>(t)), 0)...);
}
    
template <class T, class>
auto flatten_tuple(T&& t, int){
    return flatten_tuple(std::forward<T>(t), std::make_index_sequence<std::tuple_size<std::decay_t<T>>{}>());
}

template <class T>
auto flatten_tuple(T&& t){
    return flatten_tuple(std::forward<T>(t), 0);
}

template <typename T>
auto merge_tuple(T&& t)
{
    return unwrap_tuple(flatten_tuple(wrap_tuple(std::forward<T>(t))));
}

// Tests:

int main()
{
    Noisy n;
    std::tuple<std::tuple<std::tuple<std::tuple<Noisy&&, Noisy&>>>, std::tuple<std::tuple<Noisy>>> t(std::make_tuple(std::make_tuple(std::forward_as_tuple(std::move(n), n))), std::tuple<std::tuple<Noisy>>());
    std::cout << "----" << std::endl;
    
    auto x = merge_tuple(t);
    std::cout << "----" << std::endl;
    auto x2 = merge_tuple(std::move(t));
    
    std::cout << "----" << std::endl;
    static_assert(std::is_same<decltype(x), std::tuple<Noisy&&, Noisy&, Noisy>>{}, "!");
    static_assert(std::is_same<decltype(x2), std::tuple<Noisy&&, Noisy&, Noisy>>{}, "!");
}
