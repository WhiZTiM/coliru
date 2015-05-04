#include <iostream>
 
using namespace std;

struct A {};
struct B { operator A() const { return A(); } };

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
    
    cout << endl;
    
    B b1;
    B const b2;
    B& b3 = b1;
    B const& b4 = b1;
    
    z(b1); z(b2); z(b3); z(b4); 
    cout << endl;
    
    return 0;
}
