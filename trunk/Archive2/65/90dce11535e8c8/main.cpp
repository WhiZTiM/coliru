
#include <iostream>
#include <tuple>
#include <vector>
#include <type_traits>

template<class T> struct sfinaer;
template<>
struct sfinaer<std::true_type> {
    template<class F> sfinaer operator << (F f) { f([](auto& x){ return x; }); return *this; }
    template<class F> void operator >> (F f) {}
};
template<>
struct sfinaer<std::false_type> {
    template<class F> sfinaer operator << (F f) { return *this; }
    template<class F> void operator >> (F f) { f([](auto& x){ return x; }); }
};

#define STATIC_IF(...) sfinaer<std::integral_constant<bool, (__VA_ARGS__)>>{} << [&](auto local_ref) -> void
#define STATIC_ELSE >> [&](auto local_ref) -> void

template<class T>
void print_value(T&& x) {
    std::cerr << "Value: ";
    STATIC_IF(std::is_pointer<std::decay_t<T>>::value) {
        std::cerr << *local_ref(x);
    } STATIC_ELSE {
        std::cerr << local_ref(x);
    };
    std::cerr << std::endl;
}

int main(){
    int x = 42;

    print_value(x);
    print_value(&x);

}
