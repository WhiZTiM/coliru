#include <iostream>
#include <string>
#include <vector>

constexpr bool any(bool b) {
    return b;
}

template<typename... T> constexpr bool any(bool head, T... tail) {
    return head || any(tail...);
}

int main()
{
    static_assert(any(false, false, true, false), "");
}
