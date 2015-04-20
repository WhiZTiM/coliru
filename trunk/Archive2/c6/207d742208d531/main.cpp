#include <iostream>
 
int main()
{
    int array[] = {0, 1, 2, 3};
    for (int& x : array)
       x *= 2;
    
    for (int x : array)
        std::cout << x << '\n';
}