#include <iostream>
#include <string>


int square(int n) {
    int sum, count;
    for(sum = 0, count = 1; count <= n; ++count){
        sum += (1 + 2*(count - 1));
    }
    return sum;
}

int main()
{
   std::cout << square(5) << std::endl;
}
