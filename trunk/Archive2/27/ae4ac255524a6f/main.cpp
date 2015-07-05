#include <iostream>
#include <utility>

std::pair<int, float> create() {
    return std::make_pair(200, 42.0f);
}

struct foo {
    int qux;
    float bar;
    foo() {
        initQuxBar(create());
    }
    
    void initQuxBar(const std::pair<int, float>& initValues) {
        qux = initValues.first;
        bar = initValues.second;
    }
};

int main() {
    std::cout << foo().qux << std::endl;
}