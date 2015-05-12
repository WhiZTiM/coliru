#include <cstddef>

template<std::size_t N> struct choice : choice<N+1>
{
    constexpr static std::size_t max = 10;
    static_assert(N < max, "");
};
template<> struct choice<10> {};

#include <string>
#include <sstream>
namespace helper
{
    using std::to_string;
    struct has_to_string
    {
        template<typename T>
        auto requires_(T&& t) -> decltype( to_string(std::forward<T>(t)) );
    };
    
    struct has_output_operator
    {
        std::ostream& ostream();
        
        template<typename T>
        auto requires_(T&& t) -> decltype(ostream() << std::forward<T>(t));
    };
}


#include <type_traits>

template<typename T, typename = void> struct models : std::false_type {};
template<typename MF, typename... Args>
struct models<MF(Args...), decltype(MF{}.requires_(std::declval<Args>()...), void())> : std::true_type {};

#define REQUIRES(...) std::enable_if_t<models<__VA_ARGS__>::value>* = nullptr

template<typename T>
using requires = std::enable_if_t<models<T>::value, int>;


namespace detail
{
    template<typename T, requires<helper::has_to_string(T)>...>
    std::string stringify(T&& t, choice<0>)
    {
        using std::to_string;
        return to_string(std::forward<T>(t));
    }
    
    template<typename T, requires<helper::has_output_operator(T)>...>
    std::string stringify(T&& t, choice<1>)
    {
        return static_cast<std::ostringstream&>(std::ostringstream{} << std::forward<T>(t)).str();
    }
    
    template<std::size_t N>
    std::string stringify(char const(&arr)[N], choice<2>)
    {
        return std::string(arr, N);
    }
}

template<typename T>
auto stringify(T&& t) -> decltype( detail::stringify(std::forward<T>(t), choice<0>{}) )
{
    return detail::stringify(std::forward<T>(t), choice<0>{});
}

#include <iostream>

struct my_type {};
std::ostream& operator<<(std::ostream& o, my_type const&)
{
    return o << "my_type";
}

int main()
{
    std::cout << stringify("hello world") << "\n";
    std::cout << stringify(42) << "\n";
    std::cout << stringify(my_type{}) << "\n";
}