#include<memory>
#include<iostream>

    struct A
    {
        template<typename T>
        A(T const& t) : f (std::bind(&T::operator(), t)) {}
        
        void operator()() const
        {
            f();
        }
        
        std::function<void()> f;
    };
    
    struct B
    {
        void operator()() const
        {
            std::cout<<"hello"<<std::endl;
        }
    };

    int main()
    {
        A(B{}).operator()();
    }
    