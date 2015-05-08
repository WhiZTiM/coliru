#include <algorithm>
#include <iostream>

template <typename T, typename... Args> inline
T min(T t, Args... args) {
    return std::min<T>({t, args...});
}

int main() {
    std::cout << min(1) << '\n';
    std::cout << min(1, 0) << '\n';
    std::cout << min(1, 0, -1) << '\n';
    // ...
}
