#include <iostream>
#include <utility>
#include <type_traits>


template<class...> struct core_base { };
template<class... TT> struct CoreA : core_base<TT...> { };
template<class... TT> struct CoreB : core_base<TT...> { };

namespace detail
{
    template <typename T>
    struct is_derived_from_generic_CoreA
    {
        template <typename... Args>
        static std::true_type test(CoreA<Args...>*);

        static std::false_type test(void*);

        static constexpr bool value = decltype(test(std::declval<T*>())) { };
    };

    template <typename T>
    struct is_derived_from_generic_CoreB
    {
        template <typename... Args>
        static std::true_type test(CoreB<Args...>*);

        static std::false_type test(void*);

        static constexpr bool value = decltype(test(std::declval<T*>())) { };
    };
}

template <typename T>
struct is_derived_from_generic_CoreA : std::integral_constant<bool, detail::is_derived_from_generic_CoreA<T>::value> { };
template <typename T>
struct is_derived_from_generic_CoreB : std::integral_constant<bool, detail::is_derived_from_generic_CoreB<T>::value> { };

struct DerivedCoreA : CoreA<DerivedCoreA>
{
    void FooA() const { std::cout << "exec FooA" << std::endl; }
};

struct DerivedCoreB : CoreB<DerivedCoreB>
{
    void FooB() const { std::cout << "exec FooB" << std::endl; }
};

struct CoreUtilTest
{
    template <typename coretype>
    void depends_on_type(coretype const * const pct) const
    {
        if (is_derived_from_generic_CoreA<coretype>::value)
            reinterpret_cast<DerivedCoreA const * const>(pct)->FooA();
        else if (is_derived_from_generic_CoreB<coretype>::value)
            reinterpret_cast<DerivedCoreB const * const>(pct)->FooB();
    }
};

int main()
{
    CoreUtilTest CUT;
    DerivedCoreA A;
    DerivedCoreB B;
    CUT.depends_on_type(&A);
    CUT.depends_on_type(&B);    
}
