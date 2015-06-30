#include <type_traits>

template <bool C, int N>
struct CheckWithMessage : std::true_type {};

template <int N>
struct CheckWithMessage<false, N>;

int main()
{
    static_assert(CheckWithMessage<false, 10*5>{}, "!");
}