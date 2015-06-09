#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

int main()
{
    std::vector<std::vector<int>> vvi = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    std::vector<std::vector<double>> vvd;
    vvd.reserve(vvi.size());
   
    std::transform(begin(vvi), end(vvi), std::back_inserter(vvd),
                   [](const std::vector<int>& vi) { return std::vector<double>(begin(vi), end(vi)); });
   
    
    for_each(begin(vvd), end(vvd), [](const std::vector<double>& vd){
        std::copy(begin(vd), end(vd), std::ostream_iterator<double>(std::cout, " "));
        std::cout << "\n";});
}