#include <iostream>
#include <algorithm>

int main()
{
    static unsigned* Data[] = {
        new unsigned[3]{4, 5, 6},
        new unsigned[3]{1, 2, 3},
    };
    
    auto Comp = [](const unsigned* a, const unsigned* b) {return (a[0] < b[0]); };
    
    std::cout << Data[0][0] << Data[0][1] << Data[0][2] << std::endl;
    
    std::sort(std::begin(Data), std::end(Data), Comp);
    
    std::cout << Data[0][0] << Data[0][1] << Data[0][2] << std::endl;
}
