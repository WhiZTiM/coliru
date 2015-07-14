#include <iostream>
#include <vector>
#include <algorithm>


void printVector(std::vector<char> &vec)
{
//    std::for_each(vec.cbegin(), vec.cend(), [] 
//    (const char & symbol)
//    {
//        std::cout<<symbol;
//    }
//    );
    
    for(char tmp : vec)
    {
        std::cout<<tmp;
    }
}

void printReverseVector(std::vector<char> &vec)
{
    std::for_each(vec.crbegin(), vec.crend(), [] 
    (const char & symbol)
    {
        std::cout<<symbol;
    }
    );
}

void fillVector(std::vector<char> & vec)
{
    for (char i ='A'; i < ('Z'+1); ++i)
    {
        vec.push_back(i);
    }
   
}

int main()
{
    size_t size = 'Z'-'A' + 1;
    std::vector<char> myVector;
    myVector.reserve(size);
    std::cout<<"Vector capacity:" << myVector.capacity()<<std::endl; // I know that it's not size;
     
    fillVector(myVector);
    std::cout<<myVector.capacity()<<std::endl;
    
    printVector(myVector);
    std::cout<<std::endl;
    printReverseVector(myVector);
//    int i =0;
//    for(auto tmp : myVector)
//    {
//        tmp = ++i; 
//    }
    printVector(myVector);
    return 0;
}

