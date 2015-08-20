#include <iostream>
 
int main() 
{
    // range-based for uses std::begin and std::end to iterate
    // over a given range; in this case, it's an initializer list
    for (int i : {3, 1, 4, 1}) {
        std::cout << i << '\n';
    }
}