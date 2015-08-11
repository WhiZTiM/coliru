#include <iostream>
#include <string>
#include <vector>
#include <boost/algorithm/string/replace.hpp>
using namespace std;

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

void print_perm(char *str, int n, int l)
{
    if(l==n-1)
    {
        std::cout<<str<<std::endl;
        return;
    }
    for(int i=l;i<n;i++)
    {
        swap(str[l],str[i]);
        print_perm(str,n,l+1);
        swap(str[l],str[i]);
    }
}

int main()
{
    char str[] = "A";
    print_perm(str,1,0);
}
