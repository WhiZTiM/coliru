#include <iostream>
#include <string>
#include <vector>


bool isPolyndrom(std::string & src)
{
    size_t size = src.size();
        for (size_t i = 0; i <= size / 2; ++i)
        {
            if (src[i] != src[size - 1 - i])
                return false;
        }
        return true;
}   



int main()
{

//     std::string qwe = "a";
     std::cout<<isPolyndrom(std::string::string("helloworld"));
}
