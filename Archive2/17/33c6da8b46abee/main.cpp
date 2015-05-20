#include <functional>
#include <algorithm>
#include <vector>
#include <iostream>

struct XYZ
{
    float function(float x)
    {
        return x + 1.0f;
    }
};

int main()
{
    std::vector<float> foo, bar;
    foo.push_back(1.0f);
    foo.push_back(2.0f);
    
    XYZ xyz;
    
    std::transform(foo.begin(), foo.end(), std::back_inserter(bar), std::bind1st(std::mem_fun(&XYZ::function), &xyz));

    std::cout << bar[0] << " " << bar[1];
}
