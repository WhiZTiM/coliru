#include <iostream>
#include <string>
#include <vector>

using namespace std;

class abstraction
{
    public:
    virtual void f1() = 0;
    virtual void f2() = 0;
};


class impl1 //: public abstraction
{
    private:
     virtual void f1(){
        cout << "Imalenebtation1" <<endl;
    }
        
      virtual void f2(){
        cout << "Imalenebtation2" <<endl;
    }
};


int main()
{
    abstraction *p  = (abstraction*) new impl1();
    p->f1();
    p->f2();
    return 0;
}
