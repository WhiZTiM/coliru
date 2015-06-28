#include <iostream>

using namespace std;

class A
{
    int a;
public:
    A(int _a):a(_a){}
    const A& operator=(const A& a2)
    {
        a = a2.a;
        return *this;
    }
};

int main()
{
    A myA1(1), myA2(2);
    myA1 = myA2;
    return 1;
}
