#include <functional>
template< class PM >
class mem_fn_t {
    PM p;
public:
    mem_fn_t(PM p):p(p){}
    template<class... Args>
    decltype(auto) operator()(Args&&... args) {
        return std::invoke(p, std::forward<Args>(args)...);
    }
};
 
template< class R, class T >
auto mem_fn(R T::* pm){
    mem_fn_t<R T::*> t {pm};
    return t;
}