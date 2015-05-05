#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <iterator>

int g(int x, int y)
{
    return x + y;
}

int main()
{
    int t[] = { 1, 2, 3, 4 };
    std::vector<int> vecInput(t, t + 4);
    
    std::vector<double> results;
    
    const int t2VConst = 1;
    
    std::transform(vecInput.begin(), vecInput.end(), std::back_inserter(results), std::bind2nd(std::ptr_fun(&g), t2VConst));
    
    for (int i = 0; i < (int)results.size(); ++i)
    {
        std::cout << results[i] << std::endl;
    }
}
