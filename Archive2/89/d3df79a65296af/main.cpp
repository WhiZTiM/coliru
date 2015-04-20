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

template <template <typename...> class Container, typename>
struct top
{
    typedef bool type;
};

template <template <typename...> class Container, typename T>
struct top<Container, Container<T>>;


template <typename T, typename U = typename  get_inner<Data, T>::type, typename V = typename get_inner<Data, U>::type>
Data<Data<V>> Get() {
    return Data<Data<V>>{{{}, {}, {}, {}}};
}


template <typename T, typename U = typename get_inner<Data, T>::type, typename = typename top<Data, U>::type>
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
    std::cout << Get<Data<Data<int>>>().data.size() << std::endl;
    return 0;
}
