#include <iostream>

template<typename Ty>
void f_pointer(const Ty* rhs) {
    std::cout << __FUNCTION__ << rhs << std::endl;
}

template<typename Ty, size_t Dm>
void f_array(const Ty(&rhs)[Dm]) {
    std::cout << __FUNCTION__ << rhs << std::endl;
}

template<typename T>
std::enable_if_t<std::is_array<T>::value>
f(const T&t)
{
    f_array(t);
}

template<typename T>
std::enable_if_t<!std::is_array<T>::value>
f(const T&t)
{
    f_pointer(t);
}


int main(int, char*[]) {
    const char arr0[] = "test2";
    const char* ptr = "test3";
    const char arr6[6] = "test4";
    f("test1");
    f(arr0);
    f(ptr);
    f(arr6);
    return 0;
}
