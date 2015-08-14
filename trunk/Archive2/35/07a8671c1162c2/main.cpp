#include <iostream>
#include <functional>

#define FWD(xs) ::std::forward<decltype(xs)>(xs)

template<class T,class F, class... TArgs>
void forwarder(F f, TArgs&&... xs)
{
    T instance;
    std::ref(f)(instance, FWD(xs)...,0);
    //                               ^
    // example predefined argument
}

struct example
{
    void f0(int,int) {std::cout<<"#1"; }

    template<class T>
    void f1(T&&,int) { std::cout<<"#2"; }
};

int main() {
    forwarder<example>(&example::f0, 10);   
    forwarder<example>([](auto e,auto... xs){e.f1(xs...);}, 10);
}