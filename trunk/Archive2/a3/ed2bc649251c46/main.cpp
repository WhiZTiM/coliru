#include <vector>
#include <iostream> 
#include <algorithm>

int main(void)
{
    std::vector<float> v{5120.2, 5140.2, 5500.2, 5482.0, 5802.2};
    //std::vector<float> v{1, 2, 3};
    std::vector<float> result;
    size_t size = v.size();
    for (size_t i = 0; i < size; i ++) { result.insert(result.end(), v.begin(), v.end()); }
    for (size_t i = 0; i < size; i ++) {
        std::transform(v.begin(), v.end(), result.begin() + i*size, [&](float a) { return v[i] - a; });
    }
    
    for (auto c : result) { std::cout << c << ";"; }
}
