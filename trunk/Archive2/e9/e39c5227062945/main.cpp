
#include <iostream>

using namespace std;

class A
{
    public:
       A() = delete;
       A( const int & y )
       : x( y )
       {}
       
       void print() { cout << x << endl; }
    private:
       int x;
};


int main()
{
    A a(7);
    A b = a;
    b.print();
}



