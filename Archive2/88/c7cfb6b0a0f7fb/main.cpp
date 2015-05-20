#include <string>
#include <iostream>
#include <vector>

union UPtrMem
{
    void* p;
    char ach[sizeof(void*)];
};

int main(int argc, char** argv) {
    
    int m = 20;
    int n = 10;
    
    std::vector<std::vector<int>> vec(m, std::vector<int>(n));
    
    std::cout << vec.size() << " " << vec[0].size() << std::endl;
    
    std::cout << vec[0][0];
    
}