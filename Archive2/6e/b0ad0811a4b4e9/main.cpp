#include <iostream>
#include <string>
#include <sstream>
#include <functional>

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

/*
int square(int n) {
    int sum, count;
    for(sum = 0, count = 1; count <= n; ++count){
        sum += (1 + 2*(count - 1));
    }
    return sum;
}
*/

int square(size_t count){
    static int(*self)(size_t,int) = [](size_t inc, int acc) -> int {
        return inc? self(inc-1, acc+1+2*(inc-1)) : acc;
    };
    return self(count,0);
}

int main()
{
   std::cout << square(5) << std::endl;
   return 0;
}
