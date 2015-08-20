#include <functional>
#include <vector>
#include <string>
#include <iterator>
#include <algorithm>
#include <iostream>
 
int main()
{
    std::vector<std::vector<float> > v = {};
    v.assign(10, std::vector<float>());
    std::for_each(v.begin(), v.end(),
                   std::mem_fun1_ref(&std::vector<float>::reserve(10)));
}