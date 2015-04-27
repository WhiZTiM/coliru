#include <iostream>

int extract(const int* arr, const int pos) {
    return (arr[pos]);
}

int main() {
    
    int arr_a[5] = {15,25,35,45,55};
    
    std::cout << extract(arr_a, 7) << std::endl;
    
    return 0;
}
