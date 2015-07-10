#include <iostream>
#include <string>
#include <vector>


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

bool isPolyndromIter(const std::string & src)
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


int main()
{
     std::cout<<isPolyndrom(std::string("ada"));
     std::cout<<isPolyndromIter(std::string("ada"));
          std::cout<<isPolyndrom(std::string(""));
     std::cout<<isPolyndromIter(std::string(""));
}
