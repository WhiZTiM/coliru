#include <iostream>
using namespace std;

struct A
{
void f()     			{ cout << __LINE__ << “\n”;  }
void f(int)			{ cout << __LINE__ << “\n”;  }
virtual void f(const char* msg) 	{ cout << msg << “ “ << __LINE__ << “\n”; }
};

class B : A
{
public:
virtual void f(const char* msg)	{ cout << msg << “ “ << __LINE__ << “\n”; }
};

int main()
{
     B b;
     b.f();
     b.f(3);		
     A* pA = &b;
     pA->f(“abc”);
     return 0;
}
