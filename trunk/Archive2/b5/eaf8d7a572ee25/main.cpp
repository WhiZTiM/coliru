#include <iostream>
#include <string>

using namespace std;

class A
{
public:
    int m_int;
    
    A() {};
    ~A() {};
};

int main()
{
    int *iptr = 0;
    char *cptr = 0;

    iptr++;
    cptr++;

    printf("%lx ? %lx\n", (size_t)iptr, (size_t)cptr);
    printf("\r\nAlabala portocala");
    
    A* pA = new A();
    
    printf("\r\n%lx %lx", sizeof(A), sizeof(pA));
    
    delete pA;
    
    
    return 0;    
}