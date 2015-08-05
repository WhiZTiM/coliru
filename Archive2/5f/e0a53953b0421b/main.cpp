#include <iostream>
#include <functional>

int main() {
    std::function<int(int)> a=[](int x){return 2*x;};
    a=[f=a](int x){return f(x)+1;};
    std::cout << a(1);
}
