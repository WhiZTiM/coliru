#include <iostream>
#include <string>
#include <vector>

class Foo{
    public:
    std::vector<int> myVector{10};
};

int main(){
    
    Foo myfoo;
    for(auto &&element : myfoo.myVector)
        std::cout << element << ", ";
        
    std::cout << "\n";
}
