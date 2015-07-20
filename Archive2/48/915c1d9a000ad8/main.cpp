#include <type_traits>
#include <tuple>

#define REPEAT_2(M, N) M(N) M(N+1)
#define REPEAT_4(M, N)   REPEAT_2  (M, N) REPEAT_2(M, N+2)
#define REPEAT_8(M, N)   REPEAT_4  (M, N) REPEAT_4(M, N+4)
#define REPEAT_16(M, N)  REPEAT_8  (M, N) REPEAT_8(M, N+8)
#define REPEAT_32(M, N)  REPEAT_16 (M, N) REPEAT_16(M, N+16)
#define REPEAT_64(M, N)  REPEAT_32 (M, N) REPEAT_32(M, N+32)
#define REPEAT_128(M, N) REPEAT_64 (M, N) REPEAT_64(M, N+64)

template <typename... T>
class A {
    #define FRIEND(N) friend std::tuple_element_t<std::min((std::size_t)N+1, sizeof...(T)), std::tuple<void, T...>>;
    REPEAT_128(FRIEND, 0)

    static constexpr int i = 3;
};

struct X; struct Y; struct Z;
using ASpec = A<X, Y, Z>;
struct X {int i = ASpec::i;};
struct Y {int i = ASpec::i;};
struct Z {int i = ASpec::i;};

template class A<>;

int main() {}