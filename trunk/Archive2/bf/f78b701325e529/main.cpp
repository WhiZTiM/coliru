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


#include <iostream>

int main()
{
    std::cout << "sizeof(A1): " << sizeof(A1) << std::endl;
    std::cout << "sizeof(A2): " << sizeof(A2) << std::endl;
    std::cout << "sizeof(B): " << sizeof(B) << std::endl;
    
    A1* pa1;
    {
        auto b = new B;
        std::cout << "b: "<<(void*)b<<std::endl;
        pa1 = b;
        std::cout << "pa1: "<<(void*)pa1<<std::endl;
    }
    delete pa1;

    A2* pa2;
    {
        auto b = new B;
        std::cout << "b: "<<(void*)b<<std::endl;
        pa2 = b;
        std::cout << "pa2: "<<(void*)pa2<<std::endl;
    }
    delete dynamic_cast<void*>(pa2);
    return 0;
}