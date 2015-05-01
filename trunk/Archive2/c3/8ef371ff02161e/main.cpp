#include <functional>
#include <iostream>
#include <memory>

template <typename T>
using Callback = std::function<void(const T)>;

template <typename T>
void Call(const T yyy, const Callback<T>& callback) {
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
    Call(111, *callback);
    Call(222, *callback);
    return 0;
}
