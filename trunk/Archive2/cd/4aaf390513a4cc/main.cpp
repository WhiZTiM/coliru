#include <iostream>
#include <tuple>

static int test(int a, int b, int c, int d) {
    return a + b + c + d;
}

static int test(std::array<int, 4> arr) {
    return arr[0] + arr[1] + arr[2] + arr[3];
}

struct abcd {
    int a; int b; int c; int d;
};


static int test(abcd s) {
    return s.a + s.b + s.c + s.d;
}


static int test(std::tuple<int, int, int, int> tup) {
    return std::get<0>(tup) + std::get<1>(tup) + std::get<2>(tup) + std::get<3>(tup);
}

int main() {
    volatile int a, b, c, d;
    
    std::cout << test(a, b, c, d);
    std::cout << test(std::array<int, 4>{a, b, c, d});
    std::cout << test(abcd{a, b, c, d});
    std::cout << test(std::make_tuple(a, b, c, d)); 
}