#include <iostream>

template<typename T, size_t N>
void print(T (&a)[N]) { for(auto&& e:a) std::cout << e << ' '; }

int main() {
    int a[] = {1,2,3,4,5};
    print(a);
}
