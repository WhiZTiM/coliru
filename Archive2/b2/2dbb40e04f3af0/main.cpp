#include <type_traits>

template <typename, typename, typename> struct Concat;

template <typename T, template <T...> class P, T... A, T... B>
struct Concat<T, P<A...>, P<B...>> {
    using type = P<A..., B...>;
};

template <typename T, typename IndexPack> struct Make;

template <typename T, template <T...> class P, T... I, T F >
struct Make<T, P<F, I...>> {
    using type = typename Concat<T,
                                 typename Make<T, P<I>>::type,
                                 typename Make<T, P<I...>>::type>::type;
};

template <typename T, template <T...> class P, T I>
struct Make<T, P<I>> {
    using type = P<I+1, -3*I, I-1>;
};

template <int...> class Pack;

int main() {
    static_assert (std::is_same<Make<int, Pack<1,2,3,4>>::type, 
        Pack<2,-3,0, 3,-6,1, 4,-9,2, 5,-12,3>>::value, "false");
}