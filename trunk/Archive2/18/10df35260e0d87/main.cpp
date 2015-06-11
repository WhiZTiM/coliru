#include <utility>
#include <tuple>

using std::size_t;
template<int Ins, int Outs>
class Filter
{
    // implementation
};

template<int... args>
struct Chain
{
    static constexpr int my_args[] = {args...};
    
    template<size_t... Is>
    static std::tuple<Filter<my_args[Is], my_args[Is+1]>...> helper(std::index_sequence<Is...>);
    
    using type = decltype(helper(std::make_index_sequence<sizeof...(args) - 1>()));
};
    
template<class> class TD;

int main() {
    TD<Chain<5, 10, 25, 15>::type> t;    
}