#include <utility>
#include <iostream>
#include <type_traits>

// A variadic template to detect when all compile-time type
// checks evaluate to true.
template<typename...>
struct all;

template<typename T, typename... U>
struct all<T, U...> {
    enum { value = T::value && all<U...>::value };
};

template<>
struct all<> {
    enum { value = true };
};

// A variadic template to detect when one or more compile-time
// type checks evaluate to true.
template<typename...>
struct any;

template<typename T, typename... U>
struct any<T, U...> {
    enum { value = T::value || any<U...>::value };
};

template<>
struct any<> {
    enum { value = false };
};

namespace detail {
    enum class enable_if_enabler { };
}

// An enable if utility that requires all of the compile-time type checks
// to evaluate to true.
template<typename... T>
using enable_if_all = typename std::enable_if<all<T...>::value, detail::enable_if_enabler>::type;

// An enable if utility that requires one or more of the compile-time type
// checks to evaluate to true.
template<typename... T>
using enable_if_any = typename std::enable_if<any<T...>::value, detail::enable_if_enabler>::type;

// An enable if utility that requires all of the compile-time type checks
// to evaluate to false.
template<typename... T>
using disable_if_all = typename std::enable_if<!any<T...>::value, detail::enable_if_enabler>::type;

// An enable if utility that requires one or more of the compile-time type
// checks to evaluate to false.
template<typename... T>
using disable_if_any = typename std::enable_if<!all<T...>::value, detail::enable_if_enabler>::type;

// In addition to checking type traits, sometimes we can have functions that
// are ambiguos even after template instantiation.  We abuse the overload
// resolution rules to make certain overloads preferred.  We do this by
// creating an inheritance hierarchy and using the knowledge that the compiler
// prefers the function in the overload set that uses the most derived type
// to which an argument is convertible.

template<std::size_t N>
struct overload_choice : public overload_choice<N + 1> { };

template<>
struct overload_choice<30> { };

using otherwise = overload_choice<30>;

namespace {
    constexpr auto select_overload = overload_choice<0>();
}

// Now we can do some fizz-buzz stuff...
template<std::size_t N>
struct is_multiple_of_3 {
    enum { value = (N % 3 == 0) };
};

template<std::size_t N>
struct is_multiple_of_5 {
    enum { value = (N % 5 == 0) };
};

template<std::size_t N>
struct is_multiple_of_15 {
    enum { value = (N % 15 == 0) };
};

// In out fizzbuzz implementation functions, the enable ifs alone
// would cause ambiguities for numbers that are multiples of 15
// because they are also multiples of 3 and 5.  We use our overload
// selector to indicate that in those cases we prefer the impl for
// multiples of 15.
template<std::size_t N, enable_if_all<is_multiple_of_15<N>>...>
void fizzbuzz_impl(overload_choice<0>) {
    std::cout << N << " : FizzBuzz!" << std::endl;
}

template<std::size_t N, enable_if_all<is_multiple_of_5<N>>...>
void fizzbuzz_impl(overload_choice<1>) {
    std::cout << N << " : Buzz!" << std::endl;
}

template<std::size_t N, enable_if_all<is_multiple_of_3<N>>...>
void fizzbuzz_impl(overload_choice<1>) {
    std::cout << N << " : Fizz!" << std::endl;
}

template<std::size_t>
void fizzbuzz_impl(otherwise) { }

template<std::size_t... I>
void fizzbuzz(std::index_sequence<I...>) {
    auto x = { 0, (fizzbuzz_impl<I>(select_overload), 0)... };
    (void) x;
}

int main() {
    fizzbuzz(std::make_index_sequence<100>());
}