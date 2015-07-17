#include <cstdio>
#include <initializer_list>

using namespace std;

class A {
    public:
    A(const char*, void*) { printf("const char*, void*\n"); };           // #1
    A(initializer_list<char*>) { printf("initializer_list<char*>\n"); }; // #2
};

void F(const A&) {}

template<typename T> T& forward(T& t) { return t; }

int main(int, char**) {
    F({ forward("A"), new char[256]() });
}