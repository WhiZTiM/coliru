#include <iostream>
using namespace std;

int f() {
    int x = 3;
    x += 5;
    cerr << x << endl;
}

int main () {
    f();
    int (*g)() = f;
    cout << g << endl;
    cout << f << endl;
    cout << &f << endl;
    return 0;
}