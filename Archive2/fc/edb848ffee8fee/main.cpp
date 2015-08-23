#include <iostream>
#include <type_traits>


template <typename T, bool is_array>
struct f_helper {
    static void print_type (T& arg) {
        std::cout << arg << " is an array\n";
    }
};

template <typename T>
struct f_helper<T, false> {
    static void print_type (T arg) {
        std::cout << arg << " is not an array\n";
    }
};

template <typename T>
void f (T& arg) {
    f_helper<T, std::is_array<T>::value>::print_type (arg);
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