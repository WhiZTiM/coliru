#include <utility>
#include <cstdio>
#include <string>
#include <sstream>

struct S {
    virtual int f(char) const, g(int) &&; // declares two non-static member functions
};

struct D : S {
    virtual int f(char) const override;
    virtual int g(int) && override;
};
int main() {
}