#include <iostream>
 
using namespace std;

struct A { int i = 0; };

void z(A& a) { cout << "1 "; }
void z(A const& a) { cout << "2 "; }
void z(A&& a) { cout << "3 "; }

int main()
{
    A a;
    A const b;
    A& c = a;
    A& d = b;
    A const& e = a;
    A const& f = b;
    
    z(a); z(b); z(c); f(d); z(e); z(f);
    z(A()); z(a = b); z(e = c); z(A(a)); z(A(c)); z(A(e));
    
    a.i = 3;
    b.i = 5;
    c.i = 7;
    d.i = 9;
    e.i = 11;
    f.i = 13;
    
    cout << endl << a.i << " " << b.i << " " << c.i
         << " " << d.i << " " << e.i << " " << f.i << endl;
    
    return 0;
}
