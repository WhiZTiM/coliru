#include <iostream>
#include <string>
#include <vector>

template<typename T>
T foo() {
 std::cout << "first";
 return T();   
}


template<typename T, typename U>
std::pair<T,U> foo() {
 std::cout << "second";
 return std::make_pair<T,U>(T(),U()); 
}

int main()
{
    foo<int>();
    foo<int,char>();
}
