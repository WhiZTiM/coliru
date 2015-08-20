#include <utility>
#include <iostream>

template<class ... Ts>
struct enable
{
    using type = void;
};

template<class ... Ts>
using enable_t = typename enable<Ts...>::type;


template<class ... Ts>
struct CallableArgs{};

template<class F, class Args, class=void>
struct IsCallableImpl : std::false_type {};

template< class F,class ... Ts>
struct IsCallableImpl<F, CallableArgs<Ts...>, enable_t<
    decltype(std::declval<F>()(std::declval<Ts>()...))>
> : std::true_type{};


template<class F,class ... Ts>
struct IsCallable : IsCallableImpl<F,CallableArgs<Ts...>> {};


template<class F1, class F2>
struct ConditionalBasic : F1 , F2
{
    template<typename T,typename ...Ts>
    ConditionalBasic(T&& t,Ts&& ... ts)
    : F1(std::forward<T>(t)), F2(std::forward<Ts>(ts)...) {}
    
    template<class ... Args>
    auto operator()(Args&& ... args){
        return F1::operator()(std::forward<Args>(args)...);
    }
    
    template<class ... Args, std::enable_if_t<!IsCallable<F1,Args&&...>(),int> = 0>
    auto operator()(Args&& ... args){
        return F2::operator()(std::forward<Args>(args)...);
    }
};    

template<class F,class ...Fs>
struct Conditional : ConditionalBasic<F,Conditional<Fs...>>
{
    using super = ConditionalBasic<F,Conditional<Fs...>>;
    
    template<typename ... Ts>
    Conditional(Ts&& ... ts) : super(std::forward<Ts>(ts)...) {}

    using super::operator();
};

template<class F>
struct Conditional<F> : F {
    template<typename T>
    Conditional(T&& t) : F(std::forward<T>(t)) {}
    using F::operator();
};

template<class F,class ...Fs>
constexpr auto conditional(F&& f,Fs&& ... fs)
{
    return Conditional<F,Fs...>{std::forward<F>(f),std::forward<Fs>(fs)...};
}


int main()
{
    auto f = conditional(
        [](int){
            std::cout << "int" << std::endl;
        }
        ,
        [](auto){
            std::cout << "auto" << std::endl;
        }
        );
        

    f(float{0.25});
    f(std::string{});
    return 0;    
}
