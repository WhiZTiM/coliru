#include <iostream>
template <class T>
int ShellSort(T arr[], int n)
{
    int counter = 0;

    for (int gap = n / 2; gap > 0; gap /= 2)
    {

        for (int i = gap; i < n; i += 1)
        {
            ++counter;                                                    // - Add a counter here in case the third loop's case was not met at the beginning.
            T temp = arr[i];                                              // - Store the picked ith value for comparison. 

            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                ++counter;                                                // - The main counter position.
                arr[j] = arr[j - gap];                                    // - Assign the value at j to j - gap.
            }


            arr[j] = temp;                                                // - Assign whatever in temp to the last jth value to finish the swap. 
        }
    }

    return counter;
}

int main() {
    int arr[10] {10,5,7,23,6,8,2,4,672,1};
    
    for (auto it : arr) {
        std::cout << it << ' ';   
    } std::cout << '\n';
    
    int counter = ShellSort<int>(arr, 10);
    
    for (auto it : arr) {
        std::cout << it << ' ';   
    } std::cout << '\n';
    
    std::cout << "counter: " << counter << std::endl;
    return 0;
}