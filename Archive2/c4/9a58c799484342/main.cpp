#include <iostream>
#include <utility>
#include <tuple>
#include <cstddef>
#include <type_traits>

struct Noisy
{
    Noisy() { std::cout << "Noisy()" << std::endl; }
    Noisy(const Noisy&) { std::cout << "Noisy(const Noisy&)" << std::endl; }
    Noisy(Noisy&&) { std::cout << "Noisy(Noisy&&)" << std::endl; }
    ~Noisy() { std::cout << "~Noisy()" << std::endl; }
    Noisy& operator=(const Noisy&) { std::cout << "operator=(const Noisy&)" << std::endl; return *this; }
    Noisy& operator=(Noisy&&) { std::cout << "operator=(Noisy&&)" << std::endl; return *this; }
};

    template<class U, class T, bool can_move>
    struct wrapper {
        T* ptr;
        wrapper(T& t) : ptr(std::addressof(t)) {}
        
        using unwrapped_type = 
            std::conditional_t<can_move, 
                               std::conditional_t<std::is_lvalue_reference<U>{}, T&, T&&>, 
                               std::conditional_t<std::is_rvalue_reference<U>{}, T&&, T&>>;
        using tuple_element_type = U;
        
        unwrapped_type unwrap() const{
            return std::forward<unwrapped_type>(*ptr);
        }
    };


    template<class... Wrappers, std::size_t... Is>
    auto unwrap_tuple(const std::tuple<Wrappers...>& t, std::index_sequence<Is...>) {
        return std::tuple<typename Wrappers::tuple_element_type...>(std::get<Is>(t).unwrap()...);
    }
    
    template<class... Wrappers>
    auto unwrap_tuple(const std::tuple<Wrappers...>& t) {
        return unwrap_tuple(t, std::index_sequence_for<Wrappers...>());
    }


    template<bool can_move, class V, class T>
    auto wrap_and_flatten(T& t, char){
        return std::make_tuple(wrapper<V, T, can_move>(t));
    }
    template<class T> struct is_tuple : std::false_type {};
    template<class... Ts> struct is_tuple<std::tuple<Ts...>> : std::true_type {};
    template<class T> struct is_tuple<const T> : is_tuple<T> {};
    template<class T> struct is_tuple<volatile T> : is_tuple<T> {};

    template<bool can_move, class, class Tuple,
             class = std::enable_if_t<is_tuple<std::decay_t<Tuple>>{}>>
    auto wrap_and_flatten(Tuple& t, int);
    
    template<bool can_move, class Tuple, std::size_t... Is>
    auto wrap_and_flatten(Tuple& t, std::index_sequence<Is...>) {
        return std::tuple_cat(wrap_and_flatten<can_move, std::tuple_element_t<Is, std::remove_cv_t<Tuple>>>(std::get<Is>(t), 0)...);
    }
    
    template<bool can_move, class V, class Tuple, class>
    auto wrap_and_flatten(Tuple& t, int) {
        using seq_type = std::make_index_sequence<std::tuple_size<Tuple>{}>;
        return wrap_and_flatten<can_move>(t, seq_type());
    }
    
    template<class Tuple>
    auto wrap_and_flatten_tuple(Tuple&& t){
        constexpr bool can_move = !std::is_lvalue_reference<Tuple>{};
        using seq_type = std::make_index_sequence<std::tuple_size<std::decay_t<Tuple>>{}>;
        return wrap_and_flatten<can_move>(t, seq_type());
    }

    template <typename T>
    auto merge_tuple(T&& t)
    {
        return unwrap_tuple(wrap_and_flatten_tuple(std::forward<T>(t)));
    }
// Tests:
template<class> class TD;

int main()
{
    Noisy n;
    std::tuple<std::tuple<std::tuple<std::tuple<Noisy&&, Noisy&>>>, std::tuple<std::tuple<Noisy>>> t(std::make_tuple(std::make_tuple(std::forward_as_tuple(std::move(n), n))), std::tuple<std::tuple<Noisy>>());
    std::tuple<std::tuple<std::tuple<std::tuple<Noisy&&, Noisy&>>>, std::tuple<std::tuple<const Noisy, Noisy>>> t2(std::make_tuple(std::make_tuple(std::forward_as_tuple(std::move(n), n))), std::tuple<std::tuple<const Noisy, Noisy>>());
    const auto y = std::move(t);
    std::cout << "----" << std::endl;
    
    auto x = merge_tuple(t);
    std::cout << "----" << std::endl;
    auto x2 = merge_tuple(std::move(t));
    
    std::cout << "----" << std::endl;
    auto x3 = merge_tuple(y);
    std::cout << "----" << std::endl;
    auto x4 = merge_tuple(std::move(y));
    std::cout << "----" << std::endl;
    auto x5 = merge_tuple(t2);
    std::cout << "----" << std::endl;
    auto x6 = merge_tuple(std::move(t2));
    std::cout << "----" << std::endl;
    static_assert(std::is_same<decltype(x), std::tuple<Noisy&&, Noisy&, Noisy>>{}, "!");
    static_assert(std::is_same<decltype(x2), std::tuple<Noisy&&, Noisy&, Noisy>>{}, "!");
    static_assert(std::is_same<decltype(x3), std::tuple<Noisy&&, Noisy&, Noisy>>{}, "!");
    static_assert(std::is_same<decltype(x4), std::tuple<Noisy&&, Noisy&, Noisy>>{}, "!");
    static_assert(std::is_same<decltype(x5), std::tuple<Noisy&&, Noisy&, const Noisy, Noisy>>{}, "!");
    static_assert(std::is_same<decltype(x6), std::tuple<Noisy&&, Noisy&, const Noisy, Noisy>>{}, "!");
}
