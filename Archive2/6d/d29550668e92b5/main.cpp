#include <iostream>
#include <string>
#include <vector>

class A
{
public:
    void func1() { std::cout << "A::func1()" << std::endl; }
    virtual void func2() { std::cout << "A::func2()" << std::endl; }
};

class B : public A
{
public:
    void func1() { std::cout << "B::func1()" << std::endl; }
    virtual void func2() { std::cout << "B::func2()" << std::endl; }
};

int main()
{
    B b;
    b.func1();
    b.func2();
    
    A a = b;
    a.func1(); // A::func1() 실제로는 b 타입이었지만 a 로 타입슬라이스가 발생했다. 
    a.func2(); // A::func2() ..
    
    std::cout << "use pointer for check override function" << std::endl;
    A* a_ptr = &b; 
    a_ptr->func1(); // A::func1 -- a 의 포인터이고, virtual fucntion 이 아니므로 A 가 사용하는 멤버펑션 저장 주소로부터 인덱싱한 함수가 실행된다. 
    a_ptr->func2(); // B::func2 -- a 의 포인터이지만, virtual function 이므로 vtbl 을 살피게 되고, ...
    
    
    B* b_ptr = new B;
    b_ptr->func1(); // B::func1
    b_ptr->func2(); // B::func2
    return 0;
}
