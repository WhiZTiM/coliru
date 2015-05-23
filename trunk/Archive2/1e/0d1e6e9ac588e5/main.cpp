#define ABCD
#include <iostream>
 
int main()
{
 
#if defined(ABCD)
    std::cout << "3: yes\n";
#else
    std::cout << "3: no\n";
#endif
}