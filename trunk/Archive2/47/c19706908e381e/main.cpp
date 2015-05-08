#include<type_traits>
#include<iostream>

struct A
{
    A() = default;

    template<typename T>
    A(T&& t) { std::cout<<"hides copy constructor"<<std::endl; }
};

struct A_explicit
{
    A_explicit() = default;
      
    template<typename T>
    explicit A_explicit(T&& t) {  std::cout<<"does not hide copy constructor?"<<std::endl; }
};


int main()
{
    A a;
    auto b = a; (void) b;  //prints "hides copy constructor"

    A_explicit a_explicit;    
    auto b_explicit = a_explicit; (void) b_explicit; //prints nothing
}
