#include <iostream>
#include <string>
#include <vector>



int main()
{
     int a = 0b001110110;
    std::vector<int> vector = {0, 1, 2, 14, 15};
    for (auto item : vector) {
    std::cout << item << std::endl << a;
    }
}
