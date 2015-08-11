#include <iostream>

int main()
{
    int n = 5;
    int* arr = new int[n]{1,1,2,2,3};
    for(int i=0; i<n; ++i)
        std::cout << arr[i] << std::endl;
    
    return 0;
}