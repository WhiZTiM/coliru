#include <type_traits>
#include <cstring>
#include <iostream>

int main()
{
    int arr[] = {1,2,3,4,5,6,7,8,9,10};
    int index = 4;
    int size = std::extent<decltype(arr)>::value;
    std::memcpy(arr+index+1, arr+index, sizeof(arr[0])*size);
    for(int e : arr) std::cout << e << ", ";
}