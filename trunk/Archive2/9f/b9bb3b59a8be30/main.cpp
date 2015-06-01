#include <iostream>
using namespace std;

struct A {
    void id() { cout << "A ";}
};

struct B {
    void id() { cout << "B ";}
};

struct D {
    void id() { cout << "D ";}
};

struct E {
    void id() { cout << "E ";}
};


template<class A, class... As>
struct C : public A, public As... {
    void id(){
        A::id();
        using expander = int[];
        (void) expander { 0, ((void) As::id(), 0)... };
    }
};

int main(){
    C<A, B, D, E> c;
    c.id();
}