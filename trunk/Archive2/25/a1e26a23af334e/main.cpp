#include <type_traits>

template <typename T, typename = decltype(&T::mm)>
static std::true_type has_mm_impl(int);

template <typename T> static std::false_type has_mm_impl(...);

template <typename T> struct has_mm : decltype(has_mm_impl<T>(0)) {};

struct Foo { int mm; };

int main()
{
    static_assert(has_mm<Foo>::value, "Does not have mm");

// boost hana
//    auto has_mm = is_valid([](auto&& x) -> decltype((void)x.mm) { });
//    static_assert(has_mm(Foo()), "Does not have mm");
//

    return 0;
}





