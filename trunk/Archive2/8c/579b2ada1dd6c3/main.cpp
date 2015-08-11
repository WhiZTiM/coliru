#include <utility>

template <typename T>
constexpr decltype(auto) min(T&& t) {return std::forward<T>(t);}

template <typename T, typename U, typename... Args>
constexpr decltype(auto) min(T&& t, U&&u, Args&&... args) {
    return t < u? min<std::common_type_t<T, U>>(std::forward<T>(t), std::forward<Args>(args)...)
                : min<std::common_type_t<T, U>>(std::forward<U>(u), std::forward<Args>(args)...);
}

static_assert( min(0.1, 15, 'a') == 0.1 );

int main() {}