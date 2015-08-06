#include <vector>
#include <iostream> 
#include <algorithm>

int main(void)
{
    std::vector<float> v{5120.2, 5140.2, 5500.2, 5482.0, 5802.2};
    //std::vector<float> v{1, 2, 3};
    std::vector<float> result;
    size_t size = v.size();
    for (size_t i = 1; i < size; i ++) { result.insert(result.end(), v.begin() + i, v.end()); }
    size_t sum = size*(size-1)/2;
    for (size_t i = 0; i < size - 1; i ++) {
        std::transform(v.begin() + i + 1, v.end(), result.begin() + sum - (size-i)*(size-i-1)/2, [&](float a) { return v[i] - a; });
    }

    for (auto c : result) { std::cout << c << ";"; }
    
}
