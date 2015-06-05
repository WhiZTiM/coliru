template<typename...> struct dependent_false { static constexpr bool value = false; };

template<typename T>
struct testing { typedef int dummy; };

template<typename T>
struct testing<T[]> { static_assert(dependent_false<T>::value, "Failure!"); typedef int dummy; };

template<typename T, typename U = typename testing<T>::dummy>
struct test {};

int main() {
    test<int[]> x; // no failure
    // testing<int[]> y; // obvious failure
}