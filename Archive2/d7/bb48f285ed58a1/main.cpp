template <typename T, template <T...> class Pack, int Size, int Count, typename Output, T Value>
struct FillHelper;

template <typename T, template <T...> class P, int Size, int Count, T... Output, T Value>
struct FillHelper<T, P, Size, Count, P<Output...>, Value> :
    FillHelper<T, P, Size, Count + 1, P<Output..., Value>, Value> {};

template <typename T, template <T...> class P, int Size, T... Output, T Value>
struct FillHelper<T, P, Size, Size, P<Output...>, Value> {
    using type = P<Output...>;
};

template <typename T, template <T...> class P, int Size, T Value>
using Fill = typename FillHelper<T, P, Size, 0, P<>, Value>::type;

template <int...> struct Pack;

int main() {
    using T = Fill<int, Pack, 10, 4>;
}