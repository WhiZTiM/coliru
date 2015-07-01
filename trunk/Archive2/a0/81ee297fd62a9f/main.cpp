#include <iostream>

struct Test
{
    int a;
    int b;
    int c;
};

bool less(Test lhs, Test rhs)
{
return (lhs.a < rhs.a) ||
       (!(rhs.a < lhs.a) &&
        ((lhs.b < rhs.b) ||
         (!(rhs.b < lhs.b) &&
          (lhs.c < rhs.c))));
}

int main()
{
    {
        Test t1 = {8, 10, 12};
        Test t2 = {12, 10, 8};
    
        std::cout  << "less(t1 ,t2)" << less(t1, t2) << std::endl;
        std::cout  << "less(t2 ,t1)" << less(t2, t1) << std::endl;
    }
    
    std::cout << std::endl;
    
    {
        Test t1 = {8, 10, 12};
        Test t2 = {8, 9, 13};
    
        std::cout  << "less(t1 ,t2)" << less(t1, t2) << std::endl;
        std::cout  << "less(t2 ,t1)" << less(t2, t1) << std::endl;
    }

}