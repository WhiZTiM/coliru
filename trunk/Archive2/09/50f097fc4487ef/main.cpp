template<typename...> struct dependent_false { static constexpr bool value = false; };

template<typename T>
struct testing {};

template<typename T>
struct testing<T[]> { static_assert(dependent_false<T>::value, "Failure!"); };

template<typename T, typename U = testing<T>>
struct test {};

int main() {
    test<int[]> x; // no failure
    // testing<int[]> y; // obvious failure
}