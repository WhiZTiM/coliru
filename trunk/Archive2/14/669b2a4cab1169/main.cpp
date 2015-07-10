#include <iostream>

struct Foo {
    int bar() {
        auto connect = [this]{
            auto wakeup = [this]{
                return x;
            };
            return wakeup();
        };
        
        return connect();
    }
    
    int x;
};

int main() {
    Foo f{42};
    std::cout << f.bar();
}