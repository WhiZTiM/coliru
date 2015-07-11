#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct P {
   //virtual
   ~P() { cout << "Destructing P" << endl; } 
};

struct Q : virtual P {
   //virtual
   ~Q() { cout << "Destructing Q" << endl; } 
};

struct R : virtual P {
   //virtual
   ~R() { cout << "Destructing R" << endl; } 
};

struct S: R,  Q {
    int i = 10;
    int j = i + 1;
    int k = 12;
    S (int a, int b, int c):  i(a), j(b), k(c) {};   
    //S (initializer_list<int> l): i(*l.begin()), j(i + 1), k (j + 1) {}
    ~S() { cout << "Destructing S" << endl; }
};

struct B {};
struct C: B {
    B b;
    int i;
};



class Base {
    virtual void func() {}
};

class Derived : Base {
    public:
    virtual void func() override {} 
};

int main()
{
    const R* r = new S {1, 3, 3};
    //cout << s->i << ' ' << s->j << endl;;
    delete r;
    
    C c;
    cout << &c << ' ' << &c.b << ' ' << &c.i << ' ' << sizeof(C) << endl;

}
