// http://stackoverflow.com/questions/32014484/anti-sfinae-enabling-an-overload-if-a-given-expression-is-not-wellf-formed
#include <iostream>
#include <string>
using namespace std;

template<template<class...> class Template, class ...Args>
constexpr auto well_formed_default_impl(int)
    -> typename std::conditional<false,Template<Args...>, bool>::type {
        return true;
}
template<template<class...> class Template, class ...Args>
constexpr auto well_formed_default_impl(...)
    -> bool {
        return false;
}
template<template<class...> class Template, class ...Args>
constexpr bool well_formed_default() {
    return well_formed_default_impl<Template,Args...>(0);
}

template<typename T>
struct Demo {

    template<typename T2=T, typename =
        decltype( declval<T2>().length() ) // This line is the expression to test
    > struct test_for_length_method_struct { };
    template<typename T2=T>
    using test_for_length_method_alias = decltype( declval<T2>().length() );

    static
    constexpr bool T_has_length = well_formed_default< test_for_length_method_struct>();

    template<bool b = T_has_length>
    static
    auto demo_enable_if() -> typename std::enable_if<  b >::type {
        cout << "T has length" << endl;
    }
    template<bool b = T_has_length>
    static
    auto demo_enable_if() -> typename std::enable_if< !b >::type {
        cout << "T doesn't" << endl;
    }

    static
    void print_results(string type_name, bool expected) {
        cout
            << type_name
            << ": got "
            << well_formed_default     < test_for_length_method_alias, T>() // gcc unexpected here
            << " (expected " << expected << ").  well_formed_default<test_for_length_method_alias , T>"
            << endl;
        cout
            << type_name
            << ": got "
            << well_formed_default< test_for_length_method_struct, T>()
            << " (expected " << expected << ").  well_formed_default<test_for_length_method_struct , T>"
            << endl;
        cout
            << type_name
            << ": got "
            << well_formed_default     < test_for_length_method_alias>() // clang and gcc unexpected here
            << " (expected " << expected << ").  well_formed_default<test_for_length_method_alias>"
            << endl;
        cout
            << type_name
            << ": got "
            << well_formed_default< test_for_length_method_struct>()
            << " (expected " << expected << ").  well_formed_default<test_for_length_method_struct>"
            << endl;
        demo_enable_if();
    }

};


int main() {

    Demo<std::string> :: print_results("string", true);
    Demo<int>         :: print_results(" int  ", false);
}
