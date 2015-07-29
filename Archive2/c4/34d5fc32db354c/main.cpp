#include <iostream>
#include <string>
#include <vector>
#include <functional>

template<typename... Args> void bar() {
}

template<typename... Args> void f(Args&&... args) {
    bar< Args[ 5 ] ... >();
}

int main()
{
    int a[20];
    bool b[20];
    f(std::ref(a),std::ref(b));
}
