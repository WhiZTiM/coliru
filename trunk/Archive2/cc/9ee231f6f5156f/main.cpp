#include <iostream>
#include <iomanip>
#include <sstream>
#include <typeinfo>
#include <type_traits>
using namespace std;

template <int N, typename...>
struct is_n_ints : std::false_type{};

template <>
struct is_n_ints<0> : std::true_type{};

template <typename T, typename ... Ts>
struct is_n_ints<0, T, Ts...> : std::false_type{};

template <int N, typename... Ts>
struct is_n_ints<N, int, Ts...> : is_n_ints<N-1, Ts...>{};

template <int N>
struct FuncN
{
    template <typename... T>
    void operator()(T&&... ts)
    {
        static_assert(is_n_ints<N, T...>::value, "Not allowed.");
        int sum = 0;
        int helper[] __attribute__((unused)) = {(sum+=ts)...};
        cout << "Sum of args is " << sum << endl;
    }
};

int main()
{
    FuncN<3>{}(1,1,2);
    FuncN<4>{}(1,1,1);
    return 0;

}