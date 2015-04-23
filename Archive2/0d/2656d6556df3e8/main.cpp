#include <iostream>
#include <string>
#include <vector>

template<class arraytype>
void array_show(arraytype& array, size_t arraySize)
{
    // how to define mi????
    for (auto mi = std::begin(array); mi != std::end(array); mi++)
        std::cout << " " << *mi << std::endl;
}

int main()
{
    int arr[10];
    for ( int i = 0; i < 10; ++i) arr[i] = i;
    std::vector<int> vec = {31, 32, 33};
    array_show(arr, 10);
    array_show(vec, 3);
}
