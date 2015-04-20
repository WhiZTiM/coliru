#include <iostream>
#include <vector>

template <typename T>
struct Data {
    std::vector<T> data;
};

template <template <typename...> class Container, typename>
struct get_inner;

template <template <typename...> class Container, typename T>
struct get_inner<Container, Container<T>>
{
    typedef T type;
};




template <typename T, typename U = typename get_inner<Data, T>::type>
Data<U> Get() {
    return Data<U>{ {U{}, U{}} };
}

template <typename T, typename U = typename  get_inner<std::vector, T>::type>
std::vector<U> Get() {
    return std::vector<U>(3);
}

int main() {
    std::cout << Get<Data<int>>().data.size() << std::endl;  // expected output is 2
    std::cout << Get<std::vector<int>>().size() << std::endl; // expected output is 3
    return 0;
}
