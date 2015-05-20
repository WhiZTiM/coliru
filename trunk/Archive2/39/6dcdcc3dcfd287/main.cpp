
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <iostream>
#include <vector>
#include <algorithm>

std::vector<int> magic{1,2,3};

void f(std::vector<int>::const_iterator& x) 
{
    x = std::find(magic.begin(), magic.end(), 2);
}

int main()
{
    boost::function<void(std::vector<int>::const_iterator&)> bfv = boost::bind(f, _1);
    std::vector<int>::const_iterator x;
    bfv(x);
    std::cout << *x << std::endl;
}