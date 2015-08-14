#include <memory>
#include <type_traits>

template <typename...>
struct voider { using type = void; };

template <typename... Ts>
using void_t = typename voider<Ts...>::type;

template <typename, typename = void>
struct is_callable : std::false_type {};

template <typename F, typename... Args>
struct is_callable<F(Args...), void_t<decltype(std::declval<F>()(std::declval<Args>()...))>> : std::true_type {};

struct Bar {};

template <typename Function>
void foo(Function function)
{
    static_assert(is_callable<Function&(std::unique_ptr<Bar>)>{}, "Not callable");
    
    auto bar = std::make_unique<Bar>();
    
    function(std::move(bar));
}

void ok(std::unique_ptr<Bar>) {}
void nok(std::unique_ptr<Bar>&) {}

int main()
{
    foo(ok);
    foo(nok);
}
