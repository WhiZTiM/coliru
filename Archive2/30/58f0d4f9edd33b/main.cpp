#include <iostream>

// Helper alias template. (on stl since C++17)
template <bool B>
using bool_constant = std::integral_constant<bool, B>;

namespace detail {
    // Utility metafunction that maps a sequence of any types to the type void. (on stl since C++17)
    template <class... >
    using void_t = void;
    
    // Class type used to indicate detection failure. (on std::experimental)
    struct nonesuch
    {
        nonesuch() = delete;
        ~nonesuch() = delete;
        nonesuch(nonesuch const&) = delete;
        void operator=(nonesuch const&) = delete;
    };
    
    template <class AlwaysVoid, template<class...> class Op, class... Args>
    struct detector
    {
        using value_t = std::false_type;
        using type = nonesuch;
    };
    
    template <template<class...> class Op, class... Args>
    struct detector<void_t<Op<Args...>>, Op, Args...>
    {
        using value_t = std::true_type;
        using type = Op<Args...>;
    };
}

// Detection idiom (Adapted from std::experimental)
template <template<class...> class Op, class... Args>
using is_detected = typename detail::detector<void, Op, Args...>::value_t;

template <template<class...> class Op, class... Args>
using detected_t = typename detail::detector<void, Op, Args...>::type;



struct Class {
    int foo(int i) {
        return i;
    }
};


template <class T>
using foo_method_t = decltype( std::declval<T&>().foo(std::declval<int>()) );


int main()
{
    constexpr bool foo_is_detected = is_detected<foo_method_t, Class>::value;
    constexpr bool foo_has_correct_type = std::is_same<detected_t<foo_method_t, Class>, int>::value;
    std::cout << bool_constant< foo_is_detected && foo_has_correct_type >::value << std::endl;
}