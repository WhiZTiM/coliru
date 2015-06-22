#include <iostream>
#include <algorithm>

 
bool mycomp(int i, int j)
{
    return (((i < 0) && (j > 0)) || ((i > 0) && (j < 0)));
}
 
int main()
{

std::cout << std::boolalpha;

// Not antisymetric
std::cout << mycomp(2, 3) << '\n';
std::cout << mycomp(3, 2) << '\n';

// Not transitive
std::cout << mycomp(-2, -2) << '\n';
std::cout << mycomp(-3, 2) << '\n';
std::cout << mycomp(2, 2) << '\n';

}