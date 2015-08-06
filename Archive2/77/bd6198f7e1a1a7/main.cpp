#include <vector>
#include <iostream> 
#include <algorithm>


int main(void)
{
    std::vector<float> v{5120.2, 5140.2, 5500.2, 5482.0, 5802.2};
    std::transform(v.begin(), v.end(), v.begin(), [&](float a) { static float init{v[0]}; return init - a; });
    
    for (auto c : v) { std::cout << c << ";"; }
}
