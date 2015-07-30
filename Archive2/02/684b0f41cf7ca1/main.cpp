#include <iostream>
#include <cstdint>
#include <cstring>

using FloatF = float (&)();

template <FloatF f_>
struct Float {
    static constexpr auto &f = f_;
};

#define PASTE_(a, b)  a ## b
#define PASTE(a, b)   PASTE_(a, b)

#define FLT_OP(op)                                  \
template <class lhf, class rhf>                     \
constexpr float PASTE(flop_, __LINE__)() {          \
    return lhf::f() op rhf::f();                    \
}                                                   \
                                                    \
template <class lhf, class rhf>                     \
constexpr auto operator op (lhf, rhf)               \
-> Float<PASTE(flop_, __LINE__)<lhf, rhf>>

FLT_OP(+);
FLT_OP(-);
FLT_OP(*);
FLT_OP(/);

#undef FLT_OP
#undef FLT_OP_NAME

#define FLT(value)                              \
    constexpr float PASTE(flt_, __LINE__)() {   \
        return (value);                         \
    }                                           \
    Float<PASTE(flt_, __LINE__)>

#define FLOP(e) (decltype(e)::f())

// User code ////////////////////////////////////////////

FLT(3.5f) a;
FLT(4.0f) b;
FLT(1.5f) c;

int main() {
    std::cout << FLOP(a * b + c) << '\n';
}