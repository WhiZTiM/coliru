#include <iostream>

void printKLargest(int array[], int k, int size);

int main() {
    int array[5] = {1, 100, 2, 500, 6};
    int k = 3;
    int size = sizeof(array)/sizeof(array[0]);
    printKLargest(array, k, size);
    return 0;
}

void printKLargest(int array[], int k, int size) {
    int *largest = new int[k];
    for (int i = 0; i < size; i++) {
        if (array[i] > largest[0]) {
            largest[0] = array[i];
            for (int j = 1; j < k && largest[j-1] > largest[j]; j++) {
                int t = largest[j]; largest[j] = largest[j-1]; largest[j-1] = t;
            }
        }
    }
    for (int i = 0; i < k; i++) {
        std::cout << largest[i] << "\n";
    }
    delete largest;
}
