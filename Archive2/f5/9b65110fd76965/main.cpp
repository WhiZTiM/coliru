#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <string>
#include <tuple>
#include <type_traits>
#include <utility>

template <typename Tuple, typename F, std::size_t ...Indices>
void iter_tuple_impl(Tuple && tuple, F && f, std::index_sequence<Indices...>)
{
    using swallow = int[];
    (void)swallow{
        1
        , (f(std::get<Indices>(std::forward<Tuple>(tuple))), void(), int{})...
    };
}

template <typename Tuple, typename F>
void iter_tuple(Tuple && tuple, F && f)
{
    constexpr std::size_t N = std::tuple_size<std::remove_reference_t<Tuple>>::value;
    iter_tuple_impl(
        std::forward<Tuple>(tuple)
        , std::forward<F>(f)
        , std::make_index_sequence<N>{}
    );
}

int main(int, const char*[])
{
    int n = 3;
    char c = 'c';
    bool flag = true;
    std::string s = "test";
    double ldouble = 56.48;
    
    auto a = std::make_tuple(n, c, flag, s, ldouble);
    auto print_tuple = [](auto v) { iter_tuple(v, [](auto x) { std::cout << x; }); };
    
    std::cout << "OLD\n";
    print_tuple(a);
    iter_tuple(a, [](auto & x) { x = std::decay_t<decltype(x)>(); });
    std::cout << "\nNEW\n";
    print_tuple(a);

    return EXIT_SUCCESS;
}
