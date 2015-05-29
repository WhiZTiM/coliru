#include <iostream>
#include <string>
#include <vector>
#include <type_traits>


template <typename A>
struct B {
    template <typename T>
    int test(T type) {
        return test(type, std::is_lvalue_reference<T>);
    }
    template <typename T>
    int test(const T, std::true_type);
    template <typename T>
    int test(const T&);
};

template <typename A>
template<typename T>
int B<A>::test(const T& yolo, std::false_type dummy) {
    return 0;
}

template <typename A>
template <typename T>
int B<A>::test(const T yolo, std::true_type dummy) {
    return 1;
}

int main()
{
    B<int> b;
    {
        std::cout << b.test(2.0) <<  b.test(1) << std::endl;
     }
}
