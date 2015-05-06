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
    auto future = async_print(std::string{"hello world"});
    future.get();
}