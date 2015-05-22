#include <cstdio>
#include <utility>
#include <tuple>

namespace cor {
    template<typename F, typename BaseHandler>
    struct handler;
    
    struct base_handler {
        template<typename... Args>
        bool handle(Args&&... args) {
            return false;
        }
        
        template<typename F>
        auto add(F f) -> handler<F, base_handler> {
            return handler<F, base_handler>(f, this);
        }
    };
   
    template<typename F, typename BaseHandler>
    struct handler {
        using this_type = handler<F, BaseHandler>;
        
        handler(F f, BaseHandler* next) : f_(f), next_(next) {}
        
        template<typename... Args>
        bool handle(Args&&... args) {
            if (!f_(std::forward<Args>(args)...)) {
                return next_->handle(std::forward<Args>(args)...);
            } else {
                return true;
            }
        }
        
        template<typename FF>
        auto add(FF f) -> handler<FF, this_type> {
            return handler<FF, this_type>(f, this);
        }        
        
        F f_;
        BaseHandler* next_;
    };
    
    base_handler create() {
        return base_handler();
    }
    
    bool less_zero_helper(int i) {
        if (i < 0) {
            std::printf("Handler LESS zero\n");
            return true;
        } else {
            return false;
        }
    }
    
    bool greater_zero_helper(int i) {
        if (i > 0) {
            std::printf("Handler GREATER zero\n");
            return true;
        } else {
            return false;
        }
    }
}

namespace up {
    template<int... N>
    struct int_seq{};
    
    
    template<int Size, int... N>
    struct make_int_seq_helper {
        using type = typename make_int_seq_helper<Size-1, Size-1, N...>::type;
    };

    template<int... N>
    struct make_int_seq_helper<0, N...> {
        using type = int_seq<N...>;
    };

    template<int Size>
    struct make_int_seq {
        using type = typename make_int_seq_helper<Size>::type;
    };
    
    
    template<typename F, typename... Args, int... N>
    auto exec_helper(F f, const std::tuple<Args...>& t, int_seq<N...> is) {
        return f(std::get<N>(t)...);
    }
    
    template<typename F, typename... Args>
    auto exec(F f, const std::tuple<Args...>& t) {
        return exec_helper<F, Args...>(f, t, typename make_int_seq<sizeof... (Args)>::type{});
    }
}

int main() {
    cor::create().add(cor::less_zero_helper).add(cor::greater_zero_helper).handle(1);
    
    up::exec([](int i, double f){
                std::printf("%d, %.2f", i, f);
             }, 
             std::make_tuple(1, 2.0));
}
