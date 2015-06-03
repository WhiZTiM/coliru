#include <iostream>
#include <string>

int main()
{
    std::string unsorted = "37980965";
    
    for(int i = 1; i < unsorted.size(); ++i)
        for(int j = 0; j < i; ++j) {
            auto &a = unsorted[i];
            auto &b = unsorted[j];
            (((a) >= (b)) || (((a) ^= (b)), ((b) ^= (a)), ((a) ^= (b))));
        }
        
    std::cout << unsorted ;
}