#include <iostream>
#include <functional>
#include <future>
#include <string>


template <typename T>
std::future<void> print(T&& t) {
    return std::async([] (T&& message) {
        std::cout << message << std::endl;
    }, std::forward<T>(t));
}

int main() {
    auto s = std::string{"hello world"};
    auto future = print(s);
    future.get();
}