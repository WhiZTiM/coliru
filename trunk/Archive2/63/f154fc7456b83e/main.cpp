#include <cassert>
#include <utility>

namespace static_if_detail {

struct identity {
    template<typename T>
    constexpr T operator()(T&& x) const {
        return std::forward<T>(x);
    }
};

template<bool Cond>
struct statement {
    template<typename F>
    constexpr void then(const F& f){
        f(identity());
    }

    template<typename F>
    constexpr void else_(const F&){}
};

template<>
struct statement<false> {
    template<typename F>
    constexpr void then(const F&){}

    template<typename F>
    constexpr void else_(const F& f){
        f(identity());
    }
};

} //end of namespace static_if_detail

template<bool Cond, typename F>
constexpr static_if_detail::statement<Cond> static_if(F const& f){
    static_if_detail::statement<Cond> if_;
    if_.then(f);
    return if_;
}

template<class T> struct pre_inc_int {
    T value;
    template<class F>
    constexpr void operator()(F&& f) const {
      ++(f(value));   
    }
};

template<class T> struct pre_inc_A {
    T value;
    template<class F>
    constexpr void operator()(F&& f) const {
      ++(f(value.value));   
    }
};
 
template<typename T>
constexpr void foo(T& value) {
    static_if<std::is_same<T, int>{}>(pre_inc_int<decltype(value)>{value})
    .else_(pre_inc_A<decltype(value)>{value});
}

template<class T>
auto constexpr doit() -> T {
    T t{3};
    foo(t);
    return t;
}

struct A {
  int value;  
};

int main() {
    constexpr auto a = doit<int>(); 
    constexpr auto b = doit<A>();
    assert(a == 4);
    assert(b.value == 4);
   
    return 0;
}
