#include <iostream>
#include <type_traits>

//works
template<class> struct AlwaysTrue : std::true_type {};
// does not work, probably because there are no alias specializations
//template<class> using AlwaysTrue = std::true_type;

#define RECOGNIZE_MEMBER_TYPE

template <typename T>
struct foo {
    struct bar {
#ifdef RECOGNIZE_MEMBER_TYPE
      struct member_type {};
#else
      using type = T;
#endif
    };
};

template <typename T, typename = void>
struct maybeChangeType { static constexpr const char *name = "default"; };

#ifdef RECOGNIZE_MEMBER_TYPE

template <typename T>
struct maybeChangeType
<T, typename std::enable_if<AlwaysTrue<typename T::member_type>::value>::type>
{ static constexpr const char *name = "special"; };

#else

template <typename T>
struct maybeChangeType<T,
    typename std::enable_if<std::is_same<T,
                                         typename foo<typename T::type>::bar
                                         >::value
                            >::type>
{ static constexpr const char *name = "special"; };

#endif

int main() {
  std::cout << maybeChangeType<void>::name << std::endl;
  std::cout << maybeChangeType<foo<void>::bar>::name << std::endl;
}
