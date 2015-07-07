#include <stddef.h>
#include <type_traits>

template<typename T>
class Bar {
public:
    template<size_t N> struct foo{};
    template<typename> struct is_foo : std::false_type{};
    template<size_t N> struct is_foo<foo<N>> : std::true_type{};
    template<typename = typename std::enable_if<is_foo<foo<0>>::value>::type>
    Bar(int x) {}
};
int main(){
    Bar<double> b(5);
}