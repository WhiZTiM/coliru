#include <utility>

struct X { X& operator+=(const X&) { return *this; } };

#if 0
template <typename T>
T operator+(T copy_lhs, T& rhs) {
    copy_lhs += rhs;
    return copy_lhs;
}

template <typename T>
T operator+(T& lhs, T&& rhs) {
    rhs += lhs;
    return std::move(rhs); // we know rhs is an rvalue here,
                           // since if it was an lvalue, the previous
                           // overload would've been called.
}

template <typename T>
T operator+(T&& lhs, T&& rhs) {
    lhs += std::move(rhs);
    return std::move(lhs);
}

#else
template<class T>
    T operator+(const T& lhs, const T& rhs)
    {
        T tmp{lhs};
        tmp += rhs;
        return tmp;
    }
    
template<class T>
    T operator+(T&& lhs, const T& rhs)
    {
        T tmp{ std::forward<T>(lhs) };
        tmp += rhs;
        return tmp;
    }
#endif

int main()
{
    X x;
    x + x;
    X{} + x;
    x + X{};
    X{} + X{};
    const X y{};
    x + y;
    y + x;
    X{} + y;
    y + X{};
}