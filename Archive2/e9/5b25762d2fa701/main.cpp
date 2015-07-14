#include <iostream>

using namespace std;

int main()
{
    int i = 0;
    int &&rr = i;

    rr = 1;
    std::cout << rr << std::endl;
    std::cout << i << std::endl;

    return 0;
}
