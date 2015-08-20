#include <iostream>
#include <string>
#include <vector>

template <typename T>
class A
{
private:
    T m_member;

public:
    A(T _member) { std::cout << "1st version\n"; }  
    
    void foo(T param) {}
};

template <typename T>
class A<T&>
{
private:
    T& m_member;

public:
    A(T& _member) : m_member(_member) { std::cout << "2nd version\n"; }      
    
    void foo(T param) {}//still the same T, not T&
};

struct B {};
struct C {};

int main()
{
    int i{};   
    B b;
    C c;
    A<int> a1(1);//1st version
    A<int&> a2(i);//2nd version
    A<B> a3(b);//1st version
    A<B&> a4(b);//2nd version
    A<C*> a5(&c);//1st version
}
