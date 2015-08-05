#include <iostream>
#include <string>
#include <vector>



int main()
{
    int x = 1, y = 2, z = 3;
    (x = y) = z;
    std::cout << x << " " << y " " << std::endl;
    return 0;
}
