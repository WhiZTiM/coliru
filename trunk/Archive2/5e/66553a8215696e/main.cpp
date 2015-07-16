#include <functional>

template<typename Functor, typename ... Args>
auto wrapper(Functor &&f, Args &&... args) -> decltype(f(std::forward<Args>(args)...)){
    return f(std::forward<Args>(args)...);   
}

int main(){
    wrapper([]{});
}
