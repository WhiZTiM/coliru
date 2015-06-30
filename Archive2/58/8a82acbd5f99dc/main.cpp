#include <vector>
#include <algorithm>

struct X
{
    int first;
    int second;
};

#include <iostream>

int main()
{
    std::vector<X> xs = { {5, 1}, {10, 5}, {3, 2}, {10, 2} };

    std::sort(xs.begin(), xs.end(), [](X const& left, X const& right)
    {
        if (left.first > right.first)
            return true;
        
        return (left.second < right.second);
    });
    
    for (auto x : xs)
        std::cout << x.first << ": " << x.second << "\n";
}