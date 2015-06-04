#include <stdio.h>

#define CHOOSE_FOO(x1, x2, CHOICE, ...) CHOICE

#define FOO(...) CHOOSE_FOO(__VA_ARGS__, FOO2, FOO1,)(__VA_ARGS__)

#define FOO1(x) foo(x)
#define FOO2(x,x2) foo2(x,x2)

void foo(int x) {
    puts("one arg");   
}

void foo2(int x, int x2) {
    puts("two args");
}

int main(void) {
    FOO(5);
    FOO(6, 3);
}
