#include <iostream>
#include <utility>

std::pair<int, float> create() {
    return std::make_pair(200, 42.0f);
}

struct foo {
    int qux;
    float bar;
    foo() : (qux, bar)(create()) {
    }
};

int main() {
}