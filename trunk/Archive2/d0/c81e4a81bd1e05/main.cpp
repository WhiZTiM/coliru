#include <type_traits>

template<bool... B> struct all
{
    static const bool value = true;
};
template<bool b, bool... B> struct all<b, B...>
{
    static const bool value = b && all<B...>::value;
};

template<typename... A> struct only_functions
{
    static const bool value = all<std::is_function<A>::value...>::value;
};

int main()
{
    static_assert(!only_functions<void(), int>::value, "Not all arguments are functions");
    static_assert(only_functions<void(), int(double)>::value, "Not all arguments are functions");
    static_assert(all<>::value, "");
    static_assert(all<true>::value, "");
    static_assert(!all<true, false, true, true>::value, "");
    static_assert(!all<false>::value, "");
    static_assert(all<true, true, true, true, true>::value, "");
    return 0;
}



