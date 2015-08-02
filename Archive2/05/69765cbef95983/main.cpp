#include <type_traits>

struct first {
    template <typename T, typename U>
    using apply = T;
};

template <typename C, typename... Args>
struct eval {
    using type = typename C::template apply<Args...>;
};

template <typename C, typename... Args>
struct curry {
    struct type {
        template <typename... OtherArgs>
        //using apply = typename C::template apply<Args..., OtherArgs...>;
        using apply = typename eval<C, Args..., OtherArgs...>::type;
    };
};

int main() {
    static_assert(std::is_same<first::apply<int, char>, int>::value, "");
    
    using AlwaysInt = curry<first, int>::type;
    static_assert(std::is_same<AlwaysInt::apply<char>, int>::value, "");
}