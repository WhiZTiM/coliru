#include <utility>

struct MakePair
{
    template<typename... Ts>
    using type = std::pair<Ts...>;
};

struct Bind
{
    template<typename T, typename... TArgs>
    struct X {
        template<typename... TArgs2>
        using type = typename T::template type<TArgs..., TArgs2...>;
    };
    template<typename T, typename... TArgs>
    using type = X<T, TArgs...>;
};

#include <type_traits>

using PairWithInt = Bind::type<MakePair, int>;
static_assert(std::is_same<PairWithInt::type<float>, MakePair::type<int, float>>{}, "");

int main() {}