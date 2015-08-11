#include <utility>
#include <type_traits>

struct t_In{};

struct t_Out
{
    static auto Method(t_In &) -> t_Out
    {
        return(t_Out());
    }
};

template <typename...> struct voider { using type = void; };
template <typename...Ts> using void_t = typename voider<Ts...>::type;

template<typename tp_Out, typename tp_In, typename tp_Enable = void>
struct t_Template;

template<typename tp_Out, typename tp_In>
struct t_Template
<tp_Out, tp_In, void_t<decltype(tp_Out::Method(std::declval<tp_In&>()))>>
{
};
 
template <typename T> struct type_check;

int main()
{
    t_Template<t_Out, t_In> a;
}
