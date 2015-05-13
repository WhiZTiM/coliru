#include <iostream>
#include <type_traits>

struct Bar
{
    template <typename T> T value(const char* key) { return {}; }
};

template <class T>
auto foo(Bar& bar, const char* key)
    -> typename std::enable_if<!std::is_pointer<T>{}, T>::type
{
    std::cout << "Not a pointer\n";
    return bar.value<T>(key);
}

template <class T>
auto foo(Bar& bar, const char* key)
    -> typename std::enable_if<std::is_pointer<T>{}, T>::type
{
    std::cout << "Pointer\n";
    return (T)bar.value<void*>(key);
}

int main()
{
    Bar bar;
    int x = foo<int>(bar, "x");
    int* b = foo<int*>(bar, "b");
    
    (void)x;
    (void)b;
}
