template <typename T> auto foo(T t) -> decltype(foo(t)); decltype(foo(0)) x;