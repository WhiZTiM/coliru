#include<memory>
#include<vector>
#include<algorithm>
#include<iostream>

struct Abase
{
    Abase() : val(1) {}
    int val; 
};

struct A : virtual Abase
{
    A(int _val2) : val2(_val2) {}
    int val2;
};

struct B : virtual A
{
    B() : /* Abase is called implicitly here, */ A(2*val) {}
};

int main()
{
 std::cout<<B{}.val2<<std::endl;
}