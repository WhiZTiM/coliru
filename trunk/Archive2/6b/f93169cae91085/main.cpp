#include <iostream>
using namespace std;

class Int {
public:
    int v;
    Int(int a) { v = a; }
    Int &operator[](int x) {
        v+=x;
        return *this;
    }
};
ostream &operator<< (ostream &o, Int &a) {
    return o << a.v;
}

int main() {
    Int i = 2;
    cout << i[0] << i[2]; //why does it print 44 ?
    return 0;
}