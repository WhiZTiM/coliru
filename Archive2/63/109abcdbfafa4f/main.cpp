#include <initializer_list>

struct one { 
    explicit one(int, int) {}
};

struct two {
    two(int, int) {}
};

void test(one) {}
void test(two) {}

int main() {
    test({1, 2});
}