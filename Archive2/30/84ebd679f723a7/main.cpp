#include <functional>
#include <type_traits>
#include <utility>
#include <memory>

    template<class F>
    struct bind_wrapper {
        using result_type = typename F::result_type;
    
        explicit bind_wrapper(F f) : f_(std::move(f)) {}
    
        template<class... Args>
        result_type operator()(Args&&... args){
            return f(std::forward<Args>(args)...);
        }
    
    private:
        F f_;
    };

    template<class F> 
    bind_wrapper<typename std::decay<F>::type> protect(F&& f){
        return bind_wrapper<typename std::decay<F>::type>(std::forward<F>(f));
    }

void g(int, std::unique_ptr<int>&) {}

int main() {
    std::unique_ptr<int> p;
    auto fn = std::bind(g, 0, std::move(p));
    using Fn = decltype(protect(fn));
//    auto bound = [fn] {};
    auto bound = std::bind([] (const Fn &) {}, protect(std::move(fn)));
    bound();
}