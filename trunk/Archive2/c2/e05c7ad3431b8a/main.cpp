#include <iostream>
#include <cstddef>
struct S {
    int a;
    int b;
    int c;
    int d;
    int e;
};
int main()
{
    std::cout << "a:  " << offsetof(S, a) << '\n'
                        << "b:  " << offsetof(S, b) << '\n'
                        << "c:  " << offsetof(S, c) << '\n'
                        << "d:  " << offsetof(S, d) << '\n'
                        << "e:  " << offsetof(S, e) << '\n'
                        << "sizeof:  " << sizeof(S) << '\n';
}