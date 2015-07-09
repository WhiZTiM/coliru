#include <iostream>

class A
{
public:
    static void sysfct(double* var1,double* var2)
    { std::cout << "called\n"; }
    void assignFunction4B(void(*& func)(double*,double*))
    { func=&A::sysfct; }
};

class B
{
public:
    A elementofA;
    typedef  void (*funcPtr)(double*,double*);
    funcPtr sysfctinb;

    B() { this->sysfctinb=NULL; }


    void init()
    { elementofA.assignFunction4B(sysfctinb); }
};

int main()
{
    B elementofB;
    elementofB.init();
    elementofB.sysfctinb(nullptr, nullptr);
}
