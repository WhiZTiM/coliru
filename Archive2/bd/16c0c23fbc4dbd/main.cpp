#include <iostream>
#include <iterator>
#include <algorithm>

void ArrayAdd(int a[5], int b[5], int res[5])
{
    for (int i = 0; i < 5; i++)
    {
        res[i] = a[i] + b[i];
    }
}

int main()
{
    int l[] = {1,2,3,4,5};
    int j[] = {2,3,4,5,6};
    int k[5];
    ArrayAdd(l,j,k);
    std::copy(k, k + sizeof(k) / sizeof(k[0]), std::ostream_iterator<decltype(k[0])>(std::cout, " "));
}
