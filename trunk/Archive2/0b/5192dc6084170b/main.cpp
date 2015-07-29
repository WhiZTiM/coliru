#include <iostream>
#include <array>

template <int... Is>           struct IX {};
template <int N, int... Is> struct BI : BI<N-1, N-1, Is...> {};
template <int... Is>           struct BI<0, Is...> : IX<Is...> {};

template <typename T, int N, typename E, int... Is>
constexpr std::array<T,N> K( E const& e, IX<Is...>) { return std::array<T,N>{{e(Is)...}}; }

template < typename T, int N, typename E >
constexpr std::array<T,N> K(E const& e) { return K<T,N>(e,BI<N>{}); }

template< typename T >
struct Q
{
    T x,y;
	constexpr Q () : x{0}, y{x} {}
};

struct R { constexpr auto operator() ( const int ) const { return Q<int>{}; } };
constexpr auto DD = K<Q<int>,1>(R{});
int main(){
	std::cout << __VERSION__ << '\n';
}
