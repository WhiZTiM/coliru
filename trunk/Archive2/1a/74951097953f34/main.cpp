#include <vector>
#include <iostream>

int main()
{
    std::vector<int> vec{1,2,3,4,5,6};
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        float result = *it - *((it + 1 == vec.end()) ? vec.begin() : it + 1);
        std::cout << result << ' ';
    }
}
