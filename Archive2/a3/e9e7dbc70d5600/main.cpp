#include <iostream>
#include <vector>

template<typename T>
struct mystruct{
    T a;
    T b;
    typename std::vector<T> v1;
};

template<typename T>
inline void myfunc(const mystruct<T> &struct1){
    std::cout<<struct1.a<<'\t'
             <<struct1.b<<'\n';
    for(size_t i =0; i<struct1.v1.size(); i++)
        std::cout<<struct1.v1[i]<<'\n';
}

int main(){
    mystruct<float> strc1;
    strc1.a = 1.0;
    strc1.b = 2.0;
    strc1.v1.push_back(1.0);
    strc1.v1.push_back(2.0);
    myfunc(strc1);
    return 0;
}