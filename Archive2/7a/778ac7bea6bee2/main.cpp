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
    


int main() {
    constexpr int args[] = {5,10,25,15};
    Filter<args[0],args[1]> filter1;
    Filter<args[1],args[2]> filter2;
    Filter<args[2],args[3]> filter3;
    
    Chain<5, 10, 25, 15>::type tup;
    
    std::tie(filter1, filter2, filter3) = tup; // Types perfectly match
}