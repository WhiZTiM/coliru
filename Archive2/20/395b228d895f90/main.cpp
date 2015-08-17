#include <iostream>
#include <string>
#include <vector>

class A
{
    
    public :
    
       virtual void F1()
       {
           std::cout << "F1 from class A" << std::endl;
       }
       
       void F2()
       {
            std::cout << "F2 from class A" << std::endl;
       }
       
       void F3()
       {
           std::cout << "F3 from class A" << std::endl;
       }
};

class B : public A
{
    public :
    
    void F1()
    {
        std::cout << "F1 from class B" << std::endl;
    }
    void F2()
    {
        std::cout << "F2 from class B" << std::endl;
    }
    virtual void F3()
    {
        std::cout << "F3 from class B" << std::endl;
    }
};

class C : public B
{
    public :
    
    void F1()
    {
        std::cout << "F1 from class C" << std::endl;   
    }
    virtual void F2()
    {
        std::cout << "F2 from class C" << std::endl;
    }
    
    void F3()
    {
        std::cout << "F3 from class C" << std::endl;
    }
};




int main()
{
    A *a = new A;
    A *b = new B;
    B *c = new C;
    
    a->F1();
    a->F2();
    a->F3();
    
    b->F1();
    b->F2();
    b->F3();
    
    c->F1();
    c->F2();
    c->F3();
    
    
}
