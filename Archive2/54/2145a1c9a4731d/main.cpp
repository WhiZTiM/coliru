#include <iostream>
#include <utility>

template <typename D, typename B>
const D& forward_cast(const B& b) { return (const D&)b; }
template <typename D, typename B> 
D& forward_cast(B& b) { return (D&)b; }
template <typename D, typename B>
const D&& forward_cast(const B&& b) { return (const D&&)b; }
template <typename D, typename B> 
D&& forward_cast(B&& b) { return (D&&)b; }

// I see no need to use the trailing return type syntax
template <typename T, typename TT, typename R, typename... Args, typename... Argss> inline
R activate(R (T::*pfn)(Args...), TT&& obj, Argss&&... args) {
  return (forward_cast<T>(std::forward<TT>(obj)).*pfn)(std::forward<Argss>(args)...);
}

template <typename T, typename TT, typename R, typename... Args, typename... Argss> inline
R activate(R (T::*pfn)(Args...) const, TT&& obj, Argss&&... args) {
  return (forward_cast<T>(std::forward<TT>(obj)).*pfn)(std::forward<Argss>(args)...);
}

struct Type {
    enum Value {
        One,
        Two
    };
};

struct A {};

struct NonCopyable { public: NonCopyable() {} private: NonCopyable(NonCopyable const& other) {} };
struct B : public A { NonCopyable& foo(NonCopyable& other, bool test) { return other; } };
struct C : public A { NonCopyable& foo(NonCopyable& other, bool test) { return other; } }; // does something else obviously...

#define FuncSelect0(type, parent, func) \
        type == Type::One? activate(&B::func, parent) :  \
            activate(&C::func, parent)

#define FuncSelect1(type, parent, func, arg1) \
        type == Type::One? activate(&B::func, parent, arg1) :  \
            activate(&C::func, parent, arg1)

#define FuncSelect2(type, parent, func, arg1, arg2) \
        type == Type::One? activate(&B::func, parent, arg1, arg2) :  \
            activate(&C::func, parent, arg1, arg2)

#define GET_FS(_1,_2, _3, _4, _5, NAME,...) NAME
#define FuncSelect(...) (GET_FS(__VA_ARGS__, FuncSelect2, FuncSelect1, FuncSelect0)(__VA_ARGS__))

int main() {
        NonCopyable n;
        bool t;
        A* a = new B;
        NonCopyable& c = FuncSelect(Type::One, *a, foo, n, t);
        delete a;
        return 0;
}