#include <iostream>

using namespace std;

struct A
{   
    A& operator=(A const& a) = delete;
    
    int a = 3;
};

struct B
{
    int b = 5;
    
    operator A() const
    {
        A a;
        
        a.a = b;
        
        return a;
    }
};

ostream& operator<<(ostream& os, A const& a) { return os << a.a; }
ostream& operator<<(ostream& os, B const& b) { return os << b.b; }

void transform(A a) { cout << a << endl; }

int main()
{   
    B b;
    
    cout << b << endl;
    
    transform(b);
    
    A a;
    
    a = b;
    
    cout << a << endl;
    
    
    
    return 0;
}


