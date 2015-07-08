#include <vector>
#include <iostream>
// example usage

void printVec(const std::vector<int> v)
{
    for(int i = 0; i < v.size(); i++)
    {
        std::cout << v[i] << " ";
    }
    std::cout << std::endl;
}
    
int main()
{
    std::vector<int> vec(2);
    vec[0] = 100;
    vec[1] = 200;
    
    int& i = vec[0];
    
    std::cout << "i = "<< i << std::endl;
    i = 101;
    std::cout << "i = "<< i << std::endl;
    printVec(vec);
    
    i = vec.back();
    std::cout << "i = "<< i << std::endl;
    i =201;
    printVec(vec);
    
    int& i2 = vec.back();
    std::cout << "i2 = "<< i2 << std::endl;
    i2 =202;
    printVec(vec);

    return 0;
}