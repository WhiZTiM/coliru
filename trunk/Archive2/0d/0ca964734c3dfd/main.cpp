#include <iostream>
#include <utility>

struct bar {
    bar() = delete;
    bar(int a) {
        std::cout << a;
    }
};

std::pair<bar, bar> create() {
    return std::make_pair(1, 2);
}

class foo {
    private:
        bar a;
        bar b;
        foo(std::pair<bar, bar> temp, bool disambiguator) : a(temp.first), b(temp.second) {
        }
        
    public:
        foo() : foo(create(), true) {
        }
    
};

int main() {
    foo f;
}