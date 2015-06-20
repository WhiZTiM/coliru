#include <iostream>

template<typename T>
T f(T&& a, T&& b)
{
    static if(decltype(a) == const T& && decltype(b) == const T&){
        // do something different   
    }
    else{
        // do something different   
    }
}


int main()
{
    
}