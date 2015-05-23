#include <iostream>
using namespace std;

class Int;

struct Decorator
{
    Decorator(Int& i, int v) : i{i}, v{v} { }
    Int& i;
    int v;
};

class Int {
public:
    int v;
    Int(int a) { v = a; }
    Decorator operator[](int x) {
        return {*this, x};
    }
};

ostream &operator<< (ostream &o, Decorator const& d) {
    d.i.v += d.v;
    o << d.i.v;
    return o;
}

int main() {
    Int i = 2;
    cout << i[0] << i[2];
    return 0;
}