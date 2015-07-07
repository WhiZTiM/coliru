#include <iostream>
#include <type_traits>
#include <typeinfo>

/// static member of any type
namespace cpputil {
namespace detail {
    template<class T>
    constexpr auto has_static_member_classname(...)
    -> std::false_type
    {
        return {};
    }

    template<class T>
    constexpr auto has_static_member_classname(int)
    -> decltype(T::classname, void(), std::true_type())
    {
        return {};
    }

    // static member of type function that returns anything but takes no args

    template<class T>
    constexpr auto has_static_function_classname(...)
    -> std::false_type
    { return {}; }

    template<class T>
    constexpr auto has_static_function_classname(int)
    -> decltype(T::classname(), void(), std::true_type())
    { return {}; }
}
// templated free function that takes no args, used as a fallback but may be overriden

template<class T> decltype(auto) classname() { return typeid(T).name(); }

namespace detail {
    template<class T>
    constexpr auto has_free_function_classname_0(...)
    -> std::false_type
    { return {}; }

    template<class T>
    constexpr auto has_free_function_classname_0(int)
    -> decltype(classname<T>(), void(), std::true_type())
    { return {}; }

    // free function that takes a const ref

    template<class T>
    constexpr auto has_free_function_classname_1(...)
    -> std::false_type
    { return {}; }

    template<class T>
    constexpr auto has_free_function_classname_1(int)
    -> decltype(classname(std::declval<T>()), void(), std::true_type())
    { return {}; }


    template<class T, typename = void>
    struct classname_finder;

        // highest priority - if there is a free function taking 1 parameter findable by ADL - use this
        template<class T>
        struct classname_finder<
        T,
        std::enable_if_t<
        decltype(has_free_function_classname_1<T>(0))::value
        >
        >
        {
            static constexpr decltype(auto) apply() { return classname(*reinterpret_cast<const T*>(0)); }
            static constexpr decltype(auto) apply(const T& t) { return classname(t); }
        };


        // priority 2 - if there is a static function, use that
        template<class T>
        struct classname_finder<
        T,
        std::enable_if_t<
        decltype(has_static_function_classname<T>(0))::value &&
        !decltype(has_free_function_classname_1<T>(0))::value
        >
        >
        {
            static constexpr decltype(auto) apply() { return T::classname(); }
            static constexpr decltype(auto) apply(const T&) { return T::classname(); }
        };

        // priority 3 - if there is a static data member, use that
    template<class T>
    struct classname_finder<
        T,
        std::enable_if_t<
            decltype(has_static_member_classname<T>(0))::value &&
            !decltype(has_static_function_classname<T>(0))::value &&
            !decltype(has_free_function_classname_1<T>(0))::value
        >
    >
    {
        static constexpr decltype(auto) apply() { return T::classname; }
        static constexpr decltype(auto) apply(const T&) { return T::classname; }
    };

        // finally, use the cpputil::classname_of<X>() template overload
    template<class T>
    struct classname_finder<
        T,
        std::enable_if_t<
            !decltype(has_static_member_classname<T>(0))::value &&
            !decltype(has_static_function_classname<T>(0))::value &&
            !decltype(has_free_function_classname_1<T>(0))::value &&
            decltype(has_free_function_classname_0<T>(0))::value
        >
    >
    {
        static constexpr decltype(auto) apply() { return classname<T>(); }
        static constexpr decltype(auto) apply(const T&) { return classname<T>(); }
    };
}


template<class T>
auto classname_of(const T& t)
{
    return detail::classname_finder<T>::apply(t);
}

template<class T>
auto classname_of()
{
    return detail::classname_finder<T>::apply();
}
}

struct class_a
{
    static const char* classname() { return "class_a"; }
};

struct class_b
{
    constexpr static const char* classname = "class_b";
};

struct class_c
{
};
namespace cpputil {
    template<> decltype(auto) classname<class_c>() { return "class_c"; }
}

struct class_d
{
};

decltype(auto) classname(const class_d&) { return "class_d"; }

struct class_e {
    static const std::string& classname() { static const std::string _("class_e static function"); return _; }
};
static const char* classname(const class_e&) {
    return "class_e free function should take priority";
}

// no classname decoration. should fall back to typeid() solution
struct class_f {

};

using namespace std;

auto main() -> int
{
    class_a a;
    class_b b;
    class_c c;
    class_d d;
    class_e e;
    class_f f;
    cout << cpputil::classname_of(a) << endl;
    cout << cpputil::classname_of(b) << endl;
    cout << cpputil::classname_of(c) << endl;
    cout << cpputil::classname_of(d) << endl;
    cout << cpputil::classname_of(e) << endl;
    cout << cpputil::classname_of(f) << endl;
    cout << endl;

    cout << cpputil::classname_of<class_a>() << endl;
    cout << cpputil::classname_of<class_b>() << endl;
    cout << cpputil::classname_of<class_c>() << endl;
    cout << cpputil::classname_of<class_d>() << endl;
    cout << cpputil::classname_of<class_e>() << endl;
    cout << cpputil::classname_of<class_f>() << endl;

    return 0;
}