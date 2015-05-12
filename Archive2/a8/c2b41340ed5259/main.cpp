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
    int numar;
        numar=75;
    int i;
 if (numar%2 == 0) 
  numar = numar -1;
 for  (i=numar/2;i<=0;i--)
  
    std::cout <<  i*2+1<<", "<< std::endl;
}
