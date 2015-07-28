#include <iostream>
#include <string>
#include <vector>

class Foo{
    public:
    std::vector<int> 
        first{10},
        second{std::vector<int>(10,0)};
    
};

template <typename T>
void printVector(std::vector<T> &vec){
    for (auto &&element : vec)
        std::cout << element << ", ";
    std::cout << "\n";
}

int main(){
    
    Foo myfoo;
    printVector(myfoo.first);
    printVector(myfoo.second);
}
