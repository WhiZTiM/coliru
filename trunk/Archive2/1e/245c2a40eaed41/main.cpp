
#include <iostream>
#include <tuple>
#include <vector>
#include <type_traits>

template<class T> struct sfinaer;
template<>
struct sfinaer<std::true_type> {
    template<class F> sfinaer operator << (F f) { f([](auto& x)->decltype(x){ return x; }); return *this; }
    template<class F> void operator >> (F f) {}
};
template<>
struct sfinaer<std::false_type> {
    template<class F> sfinaer operator << (F f) { return *this; }
    template<class F> void operator >> (F f) { f([](auto& x)->decltype(x){ return x; }); }
};

#define STATIC_IF(...) sfinaer<std::integral_constant<bool, (__VA_ARGS__)>>{} << [&](auto local_ref) -> void
#define STATIC_ELSE >> [&](auto local_ref) -> void

template<class Tup, size_t Ix = 0U>
void print_tuple(std::ostream& ost, Tup&& tup) {
    STATIC_IF(Ix == 0) {
        ost << "{";
    };

    STATIC_IF(Ix == std::tuple_size<std::decay_t<Tup>>::value - 1) {
        ost << std::get<Ix>(tup) << "}";
    } STATIC_ELSE {
        ost << std::get<Ix>(tup) << ", ";
        print_tuple<Tup, Ix+1>(ost, std::forward<Tup>(tup));
    };
}

int main(){
    print_tuple(std::cerr, std::make_pair(3.0, "Hello"));
    std::cerr << std::endl;
    print_tuple(std::cerr, std::make_tuple("A", 42, 4.33));
    std::cerr << std::endl;

}
