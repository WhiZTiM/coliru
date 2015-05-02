#include <iostream>

class E {
    int x;
    
    class B { };
    
public:
    class I {
        B b; // error: E::B is private
        int y;
        void f(E* p, int i)
        {
            p->x = i; // error: E::x is private
            if ( &b - y ) {} 
        }
    };
    
    /*int g(I* p)
    {
        return p->y; // error: I::y is private
    }*/
};

int main()
{
    std::cout << "SUCCESS" << std::endl;    
}
