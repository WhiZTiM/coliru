#include<iostream>
#include<memory>
#include<vector>
#include<tuple>

    struct A
    {
        double a() const {std::cout<<"A.a()"<<std::endl; return 0.0;}   
        double b() const {std::cout<<"A.b()"<<std::endl; return 0.0;}   
    };

    struct B
    {
        double a() const {std::cout<<"B.a()"<<std::endl; return 0.0;}   
        double b() const {std::cout<<"B.b()"<<std::endl; return 0.0;}   
    };

    template<typename Arg>
    auto caller(Arg const& arg)
    {
        return std::make_tuple(arg.a(),arg.b());   
    }
    
    template<typename ... Args>
    void f(Args const& ... args)
    {
        std::cout<<"start f"<<std::endl;   
    }
    
    
    template<typename ... Args>
    void g(Args const& ... args)
    {
        f(caller(args) ...);
    }

    int main()
    {
        g(A{}, B{}, A{});
    }

