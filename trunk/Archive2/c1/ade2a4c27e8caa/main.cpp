#include <functional>
#include <iostream>
#include <memory>

template <typename T> struct identity { using type = T;};

template <typename T>
using Callback = std::function<void(const T)>;

template <typename T>
void Call(const T yyy, typename identity<Callback<T>>::type&& callback) {
    callback(yyy);
}

template <typename T>
class MyCallback {
public:
    explicit MyCallback(const T counter_init) : counter_{counter_init} {}
    void operator ()(const T xxx) {
        std::cout << counter_ << '\t' << xxx << std::endl;
        ++counter_;
    }
private:
    T counter_;
};

int main() {
    const auto callback = std::make_unique<MyCallback<int>>(0);
    Call(111, *callback);  // expected output is "0 \t 111"
    Call(222, *callback);  // expected output is "1 \t 222"
    return 0;
}