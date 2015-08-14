#include <iostream>
#include <string>
#include <vector>

unsigned find(int key, int* keys, unsigned size) {    
    int* origKeys = keys;
    size++;

    while(size > 1) {
        size /= 2;

        if (keys[size-1] < key)
            keys += size;
    }

    return unsigned(keys - origKeys);        
}

int main()
{
    int arr[] = { 1, 2, 3, 4, 6 };
    std::cout << find(5, arr, sizeof(arr)/sizeof(*arr)) << std::endl;
}
