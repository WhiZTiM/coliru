#include <iostream>
#include <string>
#include <sstream>

/*
int square(size_t n) 
{
    std::stringstream oss;
    oss << "The first " << n << " odd numbers are: ";
    
    int sum = 0;
    for(size_t count = 1; count <= n; ++count)
    {
        const auto nthOddNumber(1 + 2*(count - 1));
        oss << nthOddNumber << " ";
        sum += nthOddNumber;
    }
    oss << std::endl << "And their sum is " << sum;
    std::cout << oss.rdbuf() << std::endl;
    return sum;
}
*/


int square(int n) {
    int sum, count;
    for(sum = 0, count = 1; count <= n; ++count){
        sum += (1 + 2*(count - 1));
    }
    return sum;
}

int main()
{
   std::cout << square(7) << std::endl;
}
