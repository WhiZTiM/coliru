#include <vector>
#include <iostream>

template <typename Vector>
void unordered_erase(Vector& v, typename Vector::iterator it) {
    *it = std::move(v.back());    
    v.pop_back();
}

int main()
{
    std::vector<int> v = {1, 2, 3, 4, 5};
    for (auto x : v)
        std::cout << x << ' ';
    std::cout << std::endl;

    unordered_erase(v, v.begin() + 2);
    
    for (auto x : v)
        std::cout << x << ' ';
    std::cout << std::endl;
}