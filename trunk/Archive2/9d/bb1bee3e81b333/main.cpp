#include <iostream>



class Test
{
    
public :
    int i;
    
public :

    Test() : i(12) {}

    Test operator ->()
    {
        return (*this);
    }
};


int main()
{
    
    Test t;
    t->i;
    
}