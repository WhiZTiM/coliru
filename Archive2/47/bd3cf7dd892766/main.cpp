template <typename T>
T arithmetic_sum(T first) {
    return first;
}

template<typename T, typename... Types>
auto arithmetic_sum(T first, Types... others) {
    return first + arithmetic_sum(others...);
}

int main () {
    auto i = arithmetic_sum(123, 123.45, 0.55l);
}
