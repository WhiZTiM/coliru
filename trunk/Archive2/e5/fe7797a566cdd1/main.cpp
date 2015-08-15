#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>
#include <cmath>

int main()
{
    std::vector<int> foo = {-10,12,13,14,10,-20,5,6,7,20,30,1,2,3,4,9,-30};
    std::unordered_set<int> res;
    for (auto e : foo)
    {
        auto p = res.insert(abs(e));
        if(p.second == false) // not inserted
            std::cout << "opposite of " << e << " alrready exist\n";
    }
}