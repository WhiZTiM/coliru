#include <iostream>
 
using namespace std;

struct A { int i = 0; };

void z(A& a) { cout << 1 << endl; }
void z(A const& a) { cout << 2 << endl; }
void z(A&& a) { cout << 3 << endl; z(a); }

int main()
{
    z(A());
    
    return 0;
}
