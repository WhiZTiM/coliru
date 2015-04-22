#include <utility>

struct A {};
struct B : public A { int test(int i) { return i; } };
struct C : public A { int test(int i) { return i+1; } };


template<typename Child_t, typename A, typename F, typename ...Args_t>
auto activate(A& parent, F f, Args_t... args)
-> decltype( f(static_cast<Child_t&>(parent), std::forward<Args_t>(args)...) )
{ return f(static_cast<Child_t&>(parent), std::forward<Args_t>(args)...); }

template<typename Ret, typename A, typename F, typename ...Args_t>
Ret activate(int type, A& parent, F f, Args_t... args) { 
    switch (type) {
        case 0: return activate<B>(parent, f, std::forward<Args_t>(args)...);
        case 1: return activate<C>(parent, f, std::forward<Args_t>(args)...);
    }
}

struct test_wrapper
{
    template<typename O, typename... Args>
    auto operator()(O&& o, Args&&... args)
    -> decltype( std::forward<O>(o).test(std::forward<Args>(args)...) )
    {
        return std::forward<O>(o).test(std::forward<Args>(args)...);
    }
};
    
 
#include <iostream>

 
int main() {
    int type = 0;
    A* child = new B;
    std::cout << activate<int>(type, *child, test_wrapper{}, 4) << std::endl;
}