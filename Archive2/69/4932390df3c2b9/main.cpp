#include <type_traits>

template<typename... Ts> struct types {};

template<typename T, typename U> struct concat;

template<typename... Ts, typename... Us>
struct concat< types<Ts...>, types<Us...> > {
  typedef types<Ts..., Us...> result;
};

template<typename Ts, typename Us>
using Concat = typename concat<Ts, Us>::result;


template<typename Filer, std::size_t n, typename Ts> struct filter;

template<typename Filter, std::size_t n, typename... Ts>
struct filter<Filter, n, types<Ts...>> {
private:
  typedef filter<Filter, n/2, types<Ts...>> one;
  typedef filter<Filter, n-n/2, typename one::right> two;
public:
  typedef Concat< typename one::left, typename two::left > left;
  typedef typename two::right right;
};

template<typename Filter, typename... Ts>
struct filter<Filter, 0, types<Ts...>> {
  typedef types<> left;
  typedef types<Ts...> right;
};

template<typename Filter, typename T, typename... Ts>
struct filter<Filter, 1, types<T, Ts...>> {
  using left = typename std::conditional<Filter::template eval<T>(), types<T>, types<>>::type;
  typedef types<Ts...> right;
};


struct my_filter
{
    template<typename T>
    static constexpr bool eval() { return T() % 3 == 0; }
};

template<int First, int Count> struct gen_seq { using type = Concat< typename gen_seq<First, Count/2>::type, typename gen_seq<First + Count/2, Count-Count/2>::type >; };
template<int First> struct gen_seq<First, 0> { using type = types<>; };
template<int First> struct gen_seq<First, 1> { using type = types<std::integral_constant<int, First>>; };

#include <iostream>

template<typename T>
void print_type() { std::cout << __PRETTY_FUNCTION__ << "\n"; }

int main()
{
    constexpr int count = 10;
    using f = filter<my_filter, count, gen_seq<0, count>::type>;
    print_type< Concat<f::left, f::right> >();
}