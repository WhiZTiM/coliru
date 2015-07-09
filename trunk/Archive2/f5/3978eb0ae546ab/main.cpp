#include <iostream>
#include <string>
#include <vector>
#include <array>

#include <boost/algorithm/cxx11/any_of.hpp>
#include <boost/bind.hpp>

struct g
{
    bool a(const int& c)const {return c==5;}
};

std::array<g,100> cucc;

int main()
{
    return boost::algorithm::any_of(cucc, boost::bind(&g::a, 5));
}
