struct base
{
    virtual void function1() = 0;
};

struct derived : base
{
    virtual void function1() override{}
    void function2(){}
    
    virtual ~derived(){}
};


int main()
{
    derived* d = new derived;
    base* b = dynamic_cast<base*>(d);
    d->function1();
    d->function2();
    b->function1();
    delete d;
}    
