#include <algorithm>
#include <vector>
#include <iostream>
 
int main()
{
    int data[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    std::vector<int> v1(data, data+10);
 
    std::fill(v1.begin(), v1.end(), -1);
 
    for (std::vector<int>::iterator it = v1.begin(); it != v1.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";
}