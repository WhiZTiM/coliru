#include <functional>
#include <iostream>

template <typename... >
struct typelist { };

template <typename T>
struct closure_traits : closure_traits<decltype(&T::operator())> {};

#define REM_CTOR(...) __VA_ARGS__
#define SPEC(cv, var, is_var)                                              \
template <typename C, typename R, typename... Args>                        \
struct closure_traits<R (C::*) (Args... REM_CTOR var) cv>                  \
{                                                                          \
    using arity = std::integral_constant<std::size_t, sizeof...(Args) >;   \
    using is_variadic = std::integral_constant<bool, is_var>;              \
    using is_const    = std::is_const<int cv>;                             \
                                                                           \
    using result_type = R;                                                 \
                                                                           \
    template <std::size_t i>                                               \
    using arg = typename std::tuple_element<i, std::tuple<Args...>>::type; \
                                                                           \
    using args = typelist<Args...>;                                        \
};

SPEC(const, (,...), 1)
SPEC(const, (), 0)
SPEC(, (,...), 1)
SPEC(, (), 0)

struct button {
    std::function<void()> on_pressed;
    
    struct {
        int operator()(int x) {
            return x*x;
        }
    } squarer;
};

template <typename CLS, typename F, F CLS::*callable>
class wrap {
public:
    static auto make_pointer() {
        return make_pointer_impl(typename closure_traits<F>::args{});
    }
    
private:
    template <typename... Args>
    static auto make_pointer_impl(typelist<Args...> ) {
        return +[](CLS* object, Args... args) {
            return (object->*callable)(args...);
        };
    }
};

#define WRAP_MEM(CLS, MEM) wrap<CLS, decltype(CLS::MEM), &CLS::MEM>::make_pointer()

int main() {
    void (*f)(button*) = WRAP_MEM(button, on_pressed);
    int (*g)(button*, int) = WRAP_MEM(button, squarer);
    
    button b{[]{std::cout << "hi\n"; }, {}};
    f(&b);
    std::cout << g(&b, 5) << std::endl;
}