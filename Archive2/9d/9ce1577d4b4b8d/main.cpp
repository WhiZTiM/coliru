#include <iostream>
#include <string>
#include <vector>

using namespace std;

class A {
    public:
    virtual int multiply(int i) {
        cout << "A multiply" << endl;
        return 2*i ;
    }
};

class C: public A {
    public:
    int multiply(int i) { cout << "C multiply" << endl; return 5*i; }
};

class B: public A {
    public:
    int multiply(int i) {
        cout << "B multiply" << endl;
        return 3*i ;
    }
};

void print(A& a1, A& a2, A& a3) {
    cout << a1.multiply(1) << endl;
    cout << a2.multiply(1) << endl;
    cout << a3.multiply(1) << endl;
}

int main()
{
    A a;
    B b;
    a = b;
    C c;
    c = a;
    print(a, b, c);
    
    return 0;
}
