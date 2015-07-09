#include <iostream>
#include <string>
#include <vector>

void bar(std::vector<int> && x){
    for(auto &i : x ) {
        std::cout << i << std::endl;    
    }    
}

int main()
{
    const std::vector<int> words = {1,2,3,4};
    //auto foo = const_cast<std::vector<int>&>(words);
    bar(std::move(const_cast<std::vector<int>&>(words)));
}
