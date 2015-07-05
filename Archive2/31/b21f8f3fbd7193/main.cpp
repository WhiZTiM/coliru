
#include <iostream>
#include <tuple>


struct person :  std::tuple<int , std::string , bool > { 
decltype(auto)  age () { return std::get<0>(*this); }
decltype(auto)  age () const { return std::get<0>(*this); }
decltype(auto)  name () { return std::get<1>(*this); }
decltype(auto)  name () const { return std::get<1>(*this); }
decltype(auto)  is_available () { return std::get<2>(*this); }
decltype(auto)  is_available () const { return std::get<2>(*this); }
};


int main()
{
    person whoever;
    whoever.name() = "meh";
    whoever.is_available() = false;
    whoever.age() = 42;
    std::cout << std::get<0>(whoever) << " " << std::get<1>(whoever) << " " << std::get<2>(whoever);
}