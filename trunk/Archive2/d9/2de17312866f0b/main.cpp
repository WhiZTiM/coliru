#include <type_traits>
#include <iostream>
#include <utility>

template<typename T> struct voider { using type = void; };
template<typename T> using void_t = typename voider<T>::type;

template <typename Base, typename Derived>
class make_diamond {
    struct D2 : virtual Base { }; // this one MUST be virtual
                                  // otherwise we'd NEVER have a diamond
public:
    struct type : Derived, D2 { };
};

template <typename Base, typename Derived, typename = void> 
struct is_virtual_base_of : std::false_type { };

template <typename Base, typename Derived>
struct is_virtual_base_of<Base, Derived, void_t<
    decltype(static_cast<Base&>(
        std::declval<typename make_diamond<Base, Derived>::type&>()))
    >> : std::true_type { };

struct A { };
struct B : public A { };
struct C : virtual  A { };
struct D : B, C {};

int main() {
    std::cout << is_virtual_base_of<A, B>::value << std::endl; // 0
    std::cout << is_virtual_base_of<A, C>::value << std::endl; // 1
    std::cout << is_virtual_base_of<A, D>::value << std::endl; // 1
}