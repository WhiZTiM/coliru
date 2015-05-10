#include <iostream>
#include <functional>

template<typename T> struct remove_class { };
template<typename C, typename R, typename... A>
struct remove_class<R(C::*)(A...)> { using type = R(A...); };
template<typename C, typename R, typename... A>
struct remove_class<R(C::*)(A...) const> { using type = R(A...); };
template<typename C, typename R, typename... A>
struct remove_class<R(C::*)(A...) volatile> { using type = R(A...); };
template<typename C, typename R, typename... A>
struct remove_class<R(C::*)(A...) const volatile> { using type = R(A...); };

template<typename T>
struct get_signature_impl { using type = typename remove_class<
    decltype(&std::remove_reference<T>::type::operator())>::type; };
template<typename R, typename... A>
struct get_signature_impl<R(A...)> { using type = R(A...); };
template<typename R, typename... A>
struct get_signature_impl<R(&)(A...)> { using type = R(A...); };
template<typename R, typename... A>
struct get_signature_impl<R(*)(A...)> { using type = R(A...); };
template<typename T> using get_signature = typename get_signature_impl<T>::type;

template<typename F> using make_function_type = std::function<get_signature<F>>;
template<typename F> make_function_type<F> make_function(F &&f) {
    return make_function_type<F>(std::forward<F>(f)); }



struct A {
    void operator()() { std::cout << "A\n"; }
    A() = default;
//    A(const A&) = delete;
//    A(A&&) = default;
};

int f() { return 1; }

struct B {
    void operator()(int i) { std::cout << "int " << i << "\n"; }
    void operator()(float i) { std::cout << "float " << i << "\n"; }
};

int main()
{
    int k = 1;
    auto f1 = make_function([k](int i, float j) { std::cout << i << " " << j << " " << k << "\n"; });
    f1(5, 3.1);
    
//    auto f2 = make_function([](auto i, auto j) { std::cout << i << " " << j << "\n"; });


    auto f3 = make_function(A());
    f3();
    
    auto f4 = make_function(f);
    std::cout << f4() << "\n";
    
    auto f5 = make_function(&f);
    std::cout << f5() << "\n";
    
//    auto f5 = make_function(B());
}
