#include <vector>
#include <iostream>
 
int main()
{
    std::vector<int> numbers;
 
    numbers.push_back(42);
    numbers.push_bac14159); 
 
    for (int i : numbers) { // c++11 range-based for loop
        std::cout << i << '\n';
    } 
 
    return 0;
}