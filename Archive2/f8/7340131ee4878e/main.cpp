#include<utility>

template<class F, class A>
struct first_arg {
    struct template_rref {};
    struct template_lref {};
    struct template_val {};
    
    struct normal_rref{};
    struct normal_lref{};
    struct normal_val{};
    
    using return_type = decltype(std::declval<F>()(std::declval<A>()));
    
    static template_rref test(return_type (F::*)(A&&));
    static template_lref test(return_type (F::*)(A&));
    static template_val test(return_type (F::*)(A));
    static template_rref test(return_type (F::*)(A&&) const);
    static template_lref test(return_type (F::*)(A&) const);
    static template_val test(return_type (F::*)(A) const);
    
    template<class T>
    static normal_rref test(return_type (F::*)(T&&));
    
    template<class T>
    static normal_lref test(return_type (F::*)(T&));
    
    template<class T>
    static normal_val test(return_type (F::*)(T));

    template<class T>
    static normal_rref test(return_type (F::*)(T&&) const);
    
    template<class T>
    static normal_lref test(return_type (F::*)(T&) const);
    
    template<class T>
    static normal_val test(return_type (F::*)(T) const);
    
    using result = decltype(test(&F::operator()));
};
    
    
template<class> class TD;
int main() {
    auto x = [](auto){};
    auto y = [](auto&&) {};
    auto z = [](auto&){};
    TD<first_arg<decltype(x), int>::result> t1;
    TD<first_arg<decltype(y), int>::result> t2;
    TD<first_arg<decltype(z), int>::result> t3;
}