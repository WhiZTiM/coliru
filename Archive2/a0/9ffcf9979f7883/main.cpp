#include <functional>

template<typename R, typename ... Args>
R call_with(std::function<R(Args...)> f, Args ... args){
    return f(args...);
}

template<typename Functor, typename ... Args>
auto wrapper(Functor &&f, Args &&... args) -> decltype(f(std::forward<Args>(args)...)){
    return f(std::forward<Args>(args)...);   
}

int main(){
    std::function<void()> f = []{};
    call_with(f);
    
    call_with(static_cast<std::function<void()>>([]{}));
    
    wrapper([]{});
}
