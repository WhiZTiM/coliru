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
    std::function<int(size_t,int)> recurse = [&](size_t _count, int acc){
        return _count? recurse(_count-1, acc+1+2*(_count-1)) : acc;
    };
    return recurse(count,0);
}

int main()
{
   std::cout << square(5) << std::endl;
   return 0;
}
