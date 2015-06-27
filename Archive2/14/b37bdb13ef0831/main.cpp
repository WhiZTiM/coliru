#include <iostream>
using namespace std;

class A
{
protected:
    int x;
public:
    A(int x1) : x(x1) { Print(); }
    const A & operator=( const A& a)
    {
        x=a.x+1;
        return *this;
    }
    void Print() { cout << "x=" << x << endl; }
    virtual ~A() { Print(); }
};

class B: public A
{
    int y;
public:
    B(int x1, int y1): A(x1), y(y1) {}
    void Print()
    {
        A::Print();
        cout << "y=" << y << endl;
    }
    ~B(){x--;}
};

int main()
{
    B b1(1,2), b2(3,4);
    b1=b2;
    b1.Print();
    
    return 1;
}
    