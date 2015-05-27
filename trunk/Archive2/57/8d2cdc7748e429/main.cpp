#include <iostream>

using namespace std;

class A
{
    public:
    virtual void aa( int test ) { cout << test << endl; }
    virtual void aa( float test ) { cout << test << endl; }
};

class B : public A
{
public:
    template< typename T>
    void Taa ( T test ){ cout << "templated" << endl; A::aa( test); }
    
    
    virtual void aa( int test ) { Taa(test); }
    virtual void aa( float test ) { Taa(test); }
};


int main()
{      
    A* a = new B();
    
    a->aa(10);
    
    return 0;
}