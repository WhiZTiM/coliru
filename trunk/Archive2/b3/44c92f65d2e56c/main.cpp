#include <iostream>

using namespace std;

class A {

public:
    friend void func(A&);
    ~A() {
        func(*this);
    }

};

A a;

int main() {
    func(a);
    cin.get();
    return 0;
}

void func(A& a) {
    cout << "\nHello!!!\n" << endl;
}