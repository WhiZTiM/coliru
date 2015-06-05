#include <functional>
#include <type_traits>
#include <iostream>

template<class T>
struct return_type_t;
template<class R, class... Args>
struct return_type_t<R(Args...)> { using type = R; };
template<class T>
using return_type = typename return_type_t<T>::type;

template<class T,class=void>
struct function_guard;

template<class T>
struct function_guard<T,std::enable_if_t<std::is_same<return_type<T>,void>{}>>{
    template<class U>
    function_guard(U u) : callback_(std::move(u)) { }
    ~function_guard() {
        callback_();
    }
private:
    std::function<T> callback_;
};

int main()
{
    function_guard<void()> f([] { std::cout << "Bye\n"; });
    std::cout << "hello\n";
}