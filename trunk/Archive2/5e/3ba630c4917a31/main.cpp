#include <iostream>
#include <functional>
#include <future>
#include <string>


template <typename T>
std::future<void> async_print(T&& t) {
    return std::async([] (T&& message) {
        std::cout << message << std::endl;
    }, std::forward<T>(t));
}

int main() {
    auto message = std::string{"hello world"};
    auto future = async_print(message);
    future.get();
}