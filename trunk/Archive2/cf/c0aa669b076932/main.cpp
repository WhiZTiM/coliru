#include <utility>

template <typename T>
constexpr decltype(auto) min(T&& t) {return std::forward<T>(t);}

template <typename T, typename U, typename... Args>
constexpr auto min(T&& t, U&&u, Args&&... args) {
    std::common_type_t<T, U> const& _t(std::forward<T>(t)), _u(std::forward<U>(u));
    return min(_t<_u? _t : _u, std::forward<Args>(args)...);
}

static_assert( min(0.1, 15, 'a') == 0.1, "" );

int main() {}