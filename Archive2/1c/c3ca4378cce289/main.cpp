#include<iostream>
#include<functional>
#include<utility> //for std::forward

template<typename T, typename F>
void call(T&& t, F&&f)
{
    f(std::forward<T>(t));
}

struct A
{
    void foo() { std::cout<<"hello"<<std::endl; }  
};

int main()
{
    A a;
    auto f=std::bind(&A::foo, a);
    call(3,f);
}