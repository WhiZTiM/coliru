#include <iostream.h>

struct S {
    int n;
    S(int); // constructor declaration
    S() : n(7) {
        cout << n << "\n";
    } // constructor definition.
                  // ": n(7)" is the initializer list
                  // ": n(7) {}" is the function body
};
S::S(int x) : n{x} {} // constructor definition. ": n{x}" is the initializer list
int main()
{
    S s; // calls S::S()
    S s2(10); // calls S::S(int)
}