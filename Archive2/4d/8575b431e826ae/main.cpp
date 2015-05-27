#include <iostream>
#include <string>
#include <vector>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

int main()
{
    int* arr=NULL;
    int nbSlices=162;
    arr = (int *) calloc(nbSlices, sizeof(int));
    for(int i=0;i <nbSlices; ++i)
    {
        arr[i]=i;
    }
    std::vector<int> vec (arr,arr+sizeof(*arr)*nbSlices/sizeof(int));
    std::cout << arr[161] << std::endl;
    std::cout << vec.at(161) << std::endl;
}
