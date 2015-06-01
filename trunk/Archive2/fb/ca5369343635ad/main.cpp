#include <iostream>
#include <tuple>
#include <type_traits>

namespace detail
{
    template <typename T, typename... Ts> struct has_T;

    template <typename T> struct has_T<T> : std::false_type {};

    template <typename T, typename... Ts> struct has_T<T, T, Ts...>
    : std::true_type {};

    template <typename T, typename Tail, typename... Ts>
    struct has_T<T, Tail, Ts...> : has_T<T, Ts...> {};

    template <typename T, typename... Ts>
    const T& get_or_default_impl(std::true_type, const std::tuple<Ts...>& t, const T&)
    {
        return std::get<T>(t);
    }

    template <typename T, typename... Ts>
    const T& get_or_default_impl(std::false_type, const std::tuple<Ts...>&, const T& default_value)
    {
        return default_value;
    }

    template <typename T1, typename T2> struct is_included;

    template <typename... Ts>
    struct is_included<std::tuple<>, std::tuple<Ts...>> : std::true_type {};

    template <typename T, typename... Ts, typename ... Ts2>
    struct is_included<std::tuple<T, Ts...>, std::tuple<Ts2...>>
        : std::conditional_t<has_T<T, Ts2...>::value, is_included<std::tuple<Ts...>, std::tuple<Ts2...>>, std::false_type> {};

}

template <typename T, typename... Ts>
const T& get_or_default(const std::tuple<Ts...>& t, const T& default_value = T{})
{
    return detail::get_or_default_impl<T>(detail::has_T<T, Ts...>{}, t, default_value);
}

struct Day {};
struct Month {};
struct Year {};


struct Date {
public:
    Date(const Year& year, const Month& month, const Day& day) :
        d(day), m(month), y(year)
    {}

    template <typename ... Ts, typename std::enable_if_t<detail::is_included<std::tuple<Ts...>, std::tuple<Year, Month, Day>> ::value>* = nullptr>
    Date(const Ts&... ts) :
    	Date(get_or_default<const Year&>(std::tie(ts...)),
		     get_or_default<const Month&>(std::tie(ts...)),
		     get_or_default<const Day&>(std::tie(ts...)))
	{}

private:
    Day d;
    Month m;
    Year y;
};


int main() {
	Year y;
	Month m;

	Date d;

	Date d1(y, m);
	Date d2(m, y);

    //Date d3(42, "hello"); // Refused thanks to SFINAE
}
