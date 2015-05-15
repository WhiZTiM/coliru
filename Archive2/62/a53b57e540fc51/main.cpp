#include <type_traits>

template <typename T> constexpr bool IS_SCALAR = ::std::is_scalar<T>::value;
template <typename T, bool = std::integral_constant< bool, IS_SCALAR<T> >::value >
struct Class_Breaks
{
};

template <typename T, bool = ::std::is_scalar<T>::value>
struct Class_Works
{
};

void function()
{
    Class_Breaks<int> break_error;
    Class_Breaks<int, IS_SCALAR<int>> breaks_ok;
    Class_Works<int> ok;
}
