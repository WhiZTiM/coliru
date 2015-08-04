class A1
{
    virtual void a() = 0;
};

class A2
{
    virtual int a(int x) = 0;
};

class B : public A1, public A2
{
    void a() {}
    int  a(int x) { return x; }
};


int main()
{
    A1* pa1;
    pa1 = new B;
    delete pa1;

    A2* pa2;
    pa2 = new B;
    delete pa2;
    return 0;
}