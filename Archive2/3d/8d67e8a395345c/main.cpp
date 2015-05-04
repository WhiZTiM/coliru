#include <iostream>




template<typename T>
class Base
{
    public:
        void Do()
        {
            static_cast<T*>(this)->DoImpl();
        }
        
        void DoImpl()
        {
            std::cout << "Base::DoImpl\n";
        }
};



class Derived : public Base<Derived>
{
    public:
     void DoImpl()
     {
         std::cout << "Derived::DoImpl\n";
     }
};



int main()
{
    Derived d;
    Base<Derived>& b = d;
    b.Do();
    
    
    d.Do();
}