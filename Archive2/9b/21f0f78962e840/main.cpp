#include <iostream>
#include <functional>
#include <vector>
using namespace std;

class SuchString {
    public:
};

template <typename Sel, typename T>
void stringSort(T& ) {
    std::cout << "normal";
}

template <typename Sel>
void stringSort(SuchString& ) {
    std::cout << "SuchString";
}

class NormalSort {  
};
class SuchStringSort {
};


int main()
{    
    std::string sortMe;
    stringSort<NormalSort>(sortMe); // normal
    
    SuchString sortMeToo;
    stringSort<SuchStringSort>(sortMeToo); // SuchString
    
}