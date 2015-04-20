#include <iostream>
#include <vector>


int main()
{
    std::vector<int> vec;

    auto lambda = [ vec (move(vec)) ]() {
    };

}
