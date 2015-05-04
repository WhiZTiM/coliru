#include <type_traits>
template<class D>
struct B {
    B(){
        static_assert(!std::is_convertible<D*, B*>::value, "No public derivation allowed");
    }
};

struct D1 : B<D1> {};
struct D2 : private B<D2> {};

int main(){
    D1 d1;
    D2 d2;
}