#include <string>

using namespace std::literals;

constexpr int foo(int x) {
    if (x == 0) {return 1;}
    else {return "abc"s.size();}
}

int main() {
    foo(0);
    foo(1);
}