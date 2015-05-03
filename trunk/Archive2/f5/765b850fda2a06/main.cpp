#include <iostream>

using namespace std;

class Foo {
    public:
        int v;
        Foo &operator-=(const Foo &param) {
           v -= param.v; 
           return *this;
        }
        
        void bar() {
          cout << v << endl;   
        }
        
};

int main()
{
    Foo a, b;
    a.v = 10;
    b.v = 6;
    
    cout << "a: ";
    a.bar();
    
    cout << "b: ";
    b.bar();
    
    cout << "a -= b;" << endl;
    a -= b;
    
    cout << "a: ";
    a.bar();
    
    cout << "b: ";
    b.bar();
    
    return 0;
}
