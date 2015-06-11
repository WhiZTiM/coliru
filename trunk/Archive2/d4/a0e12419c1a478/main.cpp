#include<iostream>
#include<vector>
   
struct A
{
    ~A(){ std::cout << "desctruction" << std::endl; throw std::exception(); }
};

int main()
{
    A a[] = {A(), A(), A(), A(), A(), A()};
    std::vector<A> v;
    v.assign(a, a+6);
}