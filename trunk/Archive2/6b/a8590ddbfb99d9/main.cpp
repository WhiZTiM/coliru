#include<utility>
#include<functional>

struct template_rref {};
struct template_lref {};
struct template_val {};
    
struct normal_rref{};
struct normal_lref{};
struct normal_val{};

template<int R> struct rank : rank<R-1> { static_assert(R > 0, ""); };
template<> struct rank<0> {};

template<class F, class A>
struct first_arg {
    
    using return_type = decltype(std::declval<F>()(std::declval<A>()));
    using arg_type = std::decay_t<A>;
    
    
    static template_rref test(return_type (F::*)(arg_type&&), rank<5>);
    static template_lref test(return_type (F::*)(arg_type&), rank<4>);
    static template_lref test(return_type (F::*)(const arg_type&), rank<3>);
    static template_val test(return_type (F::*)(arg_type), rank<6>);
    
    static template_rref test(return_type (F::*)(arg_type&&) const, rank<5>);
    static template_lref test(return_type (F::*)(arg_type&) const, rank<4>);
    static template_lref test(return_type (F::*)(const arg_type&) const, rank<3>);
    static template_val test(return_type (F::*)(arg_type) const, rank<6>);
    
    template<class T>
    static normal_rref test(return_type (F::*)(T&&), rank<15>);
    template<class T>
    static normal_lref test(return_type (F::*)(T&), rank<14>);
    template<class T, class = std::enable_if_t<!std::is_reference<T>{}>>
    static normal_val test(return_type (F::*)(T), rank<16>);

    template<class T>
    static normal_rref test(return_type (F::*)(T&&) const, rank<15>);
    template<class T>
    static normal_lref test(return_type (F::*)(T&) const, rank<14>);
    template<class T, class = std::enable_if_t<!std::is_reference<T>{}>>
    static normal_val test(return_type (F::*)(T) const, rank<16>);
    
    using result = decltype(test(&F::operator(), rank<20>()));
};
    
    
template<class> class TD;
int main() {
    {
    #define TYPE auto
    auto x = [](TYPE){};
    auto y = [](TYPE&&) {};
    auto z = [](const TYPE&){};
    auto w = [](TYPE&){};
    TD<first_arg<decltype(x), int>::result> t1;
    TD<first_arg<decltype(y), int>::result> t2;
    TD<first_arg<decltype(z), int>::result> t3;
    TD<first_arg<decltype(z), int&>::result> t4;
    TD<first_arg<decltype(w), int&>::result> t5;
    }
    {
    #undef TYPE
    #define TYPE int
    auto x = [](TYPE){};
    auto y = [](TYPE&&) {};
    auto z = [](const TYPE&){};
    auto w = [](TYPE&){};
    TD<first_arg<decltype(x), int>::result> t1;
    TD<first_arg<decltype(y), int>::result> t2;
    TD<first_arg<decltype(z), int>::result> t3;
    TD<first_arg<decltype(z), int&>::result> t4;
    TD<first_arg<decltype(w), int&>::result> t5;
    TD<first_arg<decltype(w), std::reference_wrapper<int>>::result> t5;
    }    
    {
    #undef TYPE
    #define TYPE long
    auto x = [](TYPE){};
    auto y = [](TYPE&&) {};
    auto z = [](const TYPE&){};
    auto w = [](TYPE&){};
    TD<first_arg<decltype(x), int>::result> t1;
    TD<first_arg<decltype(y), int>::result> t2;
    TD<first_arg<decltype(z), int>::result> t3;
    TD<first_arg<decltype(z), int&>::result> t4;
    }    
}