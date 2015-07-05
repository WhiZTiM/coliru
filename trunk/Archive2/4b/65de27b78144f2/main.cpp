#include <iostream>
#include <utility>

struct bar {
    bar(int a) {
        std::cout << a;
    }
    
    bar(const bar&) = delete;
    bar(bar&&) = default;
    bar& operator=(const bar&) = delete;
    bar& operator=(bar&&) = default;
    virtual ~bar() = default;
};

std::pair<bar, bar> create() {
    return std::make_pair(1, 2);
}

class foo {
    private:
        bar a;
        bar b;
        foo(std::pair<bar, bar> temp, bool disambiguator) : a(std::move(temp.first)), b(std::move(temp.second)) {
        }
        
    public:
        foo() : foo(create(), true) {
        }
    
};

int main() {
    foo f;
}