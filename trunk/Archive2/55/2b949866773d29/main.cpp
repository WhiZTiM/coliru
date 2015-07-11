#include <iostream>
#include <map>
#include <numeric>
#include <iterator>

int main()
{
    std::map<int, int> floor_plan;
    floor_plan[0] = 1;
    floor_plan[1] = 2;

    const size_t distance = std::accumulate(std::begin(floor_plan)
                                          , std::end(floor_plan)
                                          , 0
                                          , [] (int value, const std::map<int, int>::value_type& p)
                                               { return value + p.second; });
    
    std::cout << "Total: " << distance;
}
