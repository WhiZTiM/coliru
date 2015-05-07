#include <iostream>
#include <utility>

using namespace std;

struct A {};

A&& f(A&& a)
{ return move(a); }

int main()
{
    A& a = f(A());
    
    (void)a;
    
    return 0;
}
