#include <iostream>
#include <vector>
#include <algorithm>


class A
{
    public:
        A(int x) : m_someDataMember(x) {}
        ~A() {}
        int someMethod(){ return m_someDataMember; }

    private:
        int m_someDataMember;
};

class B
{
    public:
    B(){}
    ~B(){}
    void anotherMethod(int& someInt){ /*...*/}
};

int main()
{
    A a(5);
    B b;
    b.anotherMethod(a.someMethod());
}