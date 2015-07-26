#include <functional>
#include <iostream>
#include <boost/python.hpp>

template <typename... >
struct typelist { };

template <typename T1, typename T2>
struct concat;

template <typename T1, typename T2>
using concat_t = typename concat<T1, T2>::type;

template <typename... A1, typename... A2>
struct concat<typelist<A1...>, typelist<A2...>> {
    using type = typelist<A1..., A2...>;
};

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

struct gui_button_t {
    std::function<void()> on_pressed;
};

template <typename R, typename T>
struct make_fn_ptr;

template <typename R, typename... Args>
struct make_fn_ptr<R, typelist<Args...>> {
    using type = R(*)(Args...);
};

template <typename R, typename T>
using make_fn_ptr_t = typename make_fn_ptr<R, T>::type;

template <typename CLS, typename F, F CLS::*callable>
class wrap {
public:
    using R = make_fn_ptr_t<
                    typename closure_traits<F>::result_type,
                    concat_t<
                        typelist<CLS*>,
                        typename closure_traits<F>::args
                        >
                    >;

    static R make_pointer() {
        return make_pointer_impl(typename closure_traits<F>::args{});
    }
    
private:
    template <typename... Args>
    static R make_pointer_impl(typelist<Args...> ) {
        return +[](CLS* self, Args... args) {
            return (self->*callable)(args...);
        };
    }
};

#define WRAP_MEM(CLS, MEM) wrap<CLS, decltype(CLS::MEM), &CLS::MEM>::make_pointer()

using namespace boost::python;

BOOST_PYTHON_MODULE(example)
{
    class_<gui_button_t>("GuiButton", init<>())
        .def("on_pressed", WRAP_MEM(gui_button_t, on_pressed));
}   
    