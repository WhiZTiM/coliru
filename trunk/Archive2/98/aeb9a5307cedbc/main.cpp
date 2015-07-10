#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
#include <string.h>

bool isPolyndrom(const std::string  & src)
{
    size_t size = src.size();
        for (size_t i = 0; i <= size / 2; ++i)
        {
            if (src[i] != src[size - 1 - i])
                return false;
        }
        return true;
}   

bool isPolyndromStrIter(const std::string & src)
{
    size_t size = src.size();
        for (size_t i = 0; i <= size / 2; ++i)
        {
            if (src[i] != src[size - 1 - i])
                return false;
        }
        return true;
    std::string::const_iterator it = src.cbegin();
    std::string::const_reverse_iterator rit = src.crbegin();
    while((*(it++) == *(rit++) && it != src.end()));
    return it == src.end();
}   


template <typename Iter, typename r_Iter>
bool isPolyndromIterator( Iter it,  r_Iter rit, Iter end)
{
    std::cout<<std::endl;
    Iter tmp = it;
    while(tmp!=end)
    {
        std::cout<<*tmp++;
    }
    std::cout<<" "<<std::endl;
    while((*(it++) == *(rit++)) && it != end);
    return it==end ? true : false;
} 

int main()
{
    std::cout<<isPolyndrom(std::string("ada"));
    std::cout<<isPolyndromStrIter(std::string("adA"));
    std::cout<<isPolyndrom(std::string(""));
    std::cout<<isPolyndromStrIter(std::string(""));
    std::string str = "ADA";
    std::cout<<isPolyndromIterator(str.cbegin(),str.crbegin(), str.cend());
    std::string tmp = "kazak";
    std::vector<char> vec(tmp.cbegin(), tmp.cend());
    std::cout<<isPolyndromIterator(vec.cbegin(),vec.crbegin(),vec.cend());
}
