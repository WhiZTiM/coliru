#include <type_traits>
#include <iostream>

template <typename T, typename = decltype(&T::mm)>
static std::true_type has_mm_impl(int);

template <typename T> static std::false_type has_mm_impl(...);

template <typename T> struct has_mm : decltype(has_mm_impl<T>(0)) {};

// Une version avec enable_if
template <typename T, typename = void> struct has_mm_enable_if_version : std::false_type { };

template <typename T> struct has_mm_enable_if_version<T, typename std::enable_if<bool(sizeof(&T::mm))>::type> : std::true_type { };

struct Foo { int mm; };
struct Foo2 { int mm2; };

int main()
{
    static_assert(has_mm<Foo>::value, "Does not have mm");
    static_assert(!has_mm<Foo2>::value, "Has mm");    
    static_assert(has_mm_enable_if_version<Foo>::value, "Does not have mm");
    static_assert(has_mm_enable_if_version<Foo>::value, "Has mm");    

// boost hana
//    auto has_mm = is_valid([](auto&& x) -> decltype((void)x.mm) { });
//    static_assert(has_mm(Foo()), "Does not have mm");
//

    std::cout << "hi w0rld" << std::endl;

    return 0;
}





