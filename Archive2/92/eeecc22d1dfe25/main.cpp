#include <iostream>

    template<typename T>
    auto foo(T&& t) { std::cout<<"general version"<<std::endl; }

    struct A {};
    
    //auto foo(A a) { std::cout<<"A"<<std::endl; }
    auto foo(A & a) { std::cout<<"A&"<<std::endl; }
    auto foo(A const& a) { std::cout<<"A const&"<<std::endl; }
    auto foo(A && a) { std::cout<<"A &&"<<std::endl; }
    auto foo(A const&& a) { std::cout<<"A const&&"<<std::endl; }

    int main()
    {
        A a;
        const A aconst;
    
        foo(a);
        foo(aconst);
        foo(std::move(a));
        foo(std::move(aconst));
    }
