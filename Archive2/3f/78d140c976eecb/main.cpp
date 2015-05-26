#include <iostream>
#include <string>
#include <vector>

    template<class ...> using void_t = void;
    
    
    struct A {};
    
    struct B
    {
        using foo_t=double;    
    };
    
    
    struct C
    {
        template<typename T, typename = void_t<typename T::foo_t> >
        void foo(T const& t)
        {
            std::cout<<"hello"<<std::endl;
        }
    };
    
    int main()
    {
        //C{}.foo(A{});
        C{}.foo(B{});
    }