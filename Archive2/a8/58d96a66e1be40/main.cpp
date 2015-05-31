#include <cstring>

struct A {
    char a[123];
    A (const char *p) {std::strcpy(a,p);}
};

int main () {
    A a("Hello");
}