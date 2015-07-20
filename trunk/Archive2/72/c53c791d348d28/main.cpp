#include <tuple>
#include <type_traits>
#include <utility>

struct empty {using type = empty;};
template <std::size_t N, typename... T>
struct fill {
    template <typename=std::make_index_sequence<N>> struct aux;
	template <std::size_t... I> struct aux<std::index_sequence<I...>> {
		using type = std::tuple<typename std::conditional_t<I < sizeof...(T), std::tuple_element<I, std::tuple<T...>>, empty>::type...>;
	};
	using type = typename aux<>::type;
};

#define REPEAT_2(M, N) M(N) M(N+1)
#define REPEAT_4(M, N)   REPEAT_2  (M, N) REPEAT_2(M, N+2)
#define REPEAT_8(M, N)   REPEAT_4  (M, N) REPEAT_4(M, N+4)
#define REPEAT_16(M, N)  REPEAT_8  (M, N) REPEAT_8(M, N+8)
#define REPEAT_32(M, N)  REPEAT_16 (M, N) REPEAT_16(M, N+16)
#define REPEAT_64(M, N)  REPEAT_32 (M, N) REPEAT_32(M, N+32)
#define REPEAT_128(M, N) REPEAT_64 (M, N) REPEAT_64(M, N+64)

template <typename... T>
class A {
	#define FRIEND(N) friend std::tuple_element_t<N, typename fill<128, T...>::type>;
	REPEAT_128(FRIEND, 0)

	static constexpr int i = 3;
};

class X; class Y; class Z;
using ASpec = A<X, Y, Z>;
class X {static const int i = ASpec::i;};
class Y {static const int i = ASpec::i;};
class Z {static const int i = ASpec::i;};

int main() {}
