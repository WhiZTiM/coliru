#include <type_traits>

template<typename T, typename = typename std::enable_if<std::is_same<T, int>::value>::type>
void do_the_thing() {}

template<typename T, typename std::enable_if<std::is_same<T, int>::value, int>::type = 0>
void also_do_the_thing() {}

int main() {
    do_the_thing<int>();
    also_do_the_thing<int>();
}