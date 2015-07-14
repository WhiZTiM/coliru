#include <cassert>
#include <type_traits>

template<typename T>
constexpr void foo(T& value, std::true_type) {
    ++value;
}

template<typename T>
constexpr void foo(T& value, std::false_type) {
    ++(value.value);
}

template<class T>
auto constexpr doit() -> T {
    T t{3};
    foo(t, std::is_same<T, int>{});
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
