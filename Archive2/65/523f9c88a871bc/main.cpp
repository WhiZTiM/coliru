#include <vector>
#include <iostream>

template<std::vector<int>& v>
void f() {
    std::cout << v.size() << "\n";
}

std::vector<int> vec;
int main(int argc, char** argv) {
    f<vec>();
    vec.push_back(42);
    f<vec>();
    return 0;
}