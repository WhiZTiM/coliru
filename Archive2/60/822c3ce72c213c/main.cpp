#include <iostream>
#include <vector>


int main()
{
    std::vector<int> vector = { 1, 2, 3, 4 };
    std::cout << *vector.begin()++++;
}
