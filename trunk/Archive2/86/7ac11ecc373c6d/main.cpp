#include <tuple>

// ALL THE TYPES
template <typename...> 
struct stuff { typedef stuff type; };
template <std::size_t...> 
struct indices_list { typedef indices_list type; };
template <std::size_t N, std::size_t... I>
struct indices : public indices<N-1, N-1, I...> { };
template <std::size_t... I>
struct indices<0, I...> : public indices_list<I...>{ };
template <typename T>
struct tuple_indices : public indices<std::tuple_size<T>::value>{ };

template <typename TArf, typename T>
// Can't just have one argument, because we're also trimming down `stuff` or `indices_list`
// which means we need a second one. This is so unintuitive and clogged up =/
//auto awesome_tuple_dog ( T&& item ) {
// don't care about "Arf", just want "T"
// TArf matches anything, whether "stuff" or "indices_list"
auto awesome_tuple_dog ( TArf, T&& item ) {
    return std::forward<T>( item );
}

template <std::size_t... I, typename... Indices, typename T, typename... Tn>
// `stuff` OP: it captures everything, and we just "select" what we want
// pretty broken that was have to do it this way, IMO. Wish there was a better way to meta-program =/
auto awesome_tuple_cat( stuff<indices_list<I...>, Indices...>, T&& item, Tn&&... meow ) {
    return awesome_tuple_dog( stuff<indices_list<I...>, Indices...>(), // make another "stuff" 
                                std::make_tuple( std::get<I>( item )... ), // make a tuple out of what we have (indices can be nothing but `0`)
                                std::forward<Tn>( meow )... // And keep going until we're done
                                );
}

template <typename... Tn>
auto awesome_tuple_cat( Tn&&... meow ) {
    // Encapsulate all necessary info in "stuff", to get infinite deduction
    // fucking typename D:< at least we can get the type out of indices_list, though
    // thanks to the typedef
    return awsome_tuple_dog( stuff<typename tuple_indices<Tn>::type...>(), std::forward<Tn>( meow )... );
}

int main() {
    
    std::tuple<int, float, double> kitty;
    long long doggy;
    std::pair<unsigned, unsigned long long> cat;
    
    struct make_error {} test = awesome_tuple_cat( kitty, std::tie( doggy ), cat );
}