#include <iostream>

using namespace std;

struct A;

struct B
{
    int b = 5;
    
    operator A() ;
};

struct A
{   
    int a = 3;
    friend B::operator A();
};



B::operator A() 
    {
        A a;
        
        a.a = b;
        
        return a;
    }

ostream& operator<<(ostream& os, A const& a) { return os << a.a; }
ostream& operator<<(ostream& os, B const& b) { return os << b.b; }

//void transform(A a) { cout << a << endl; }

int main()
{   
    B b;
    
    cout << b << endl;
    
    //transform(b);
    
    A a=b;
    

    
    cout << a << endl;
    
    
    
    return 0;
}


