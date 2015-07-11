#include <iostream>
#include <map>
#include <numeric>
#include <iterator>
#include <boost/range/numeric.hpp>
#include <boost/range/adaptor/map.hpp>

int main()
{
    std::map<int, int> floor_plan;
    floor_plan[0] = 1;
    floor_plan[1] = 2;
                    
    const size_t distance = boost::accumulate(floor_plan | boost::adaptors::map_values, 0);
    
    std::cout << "Total: " << distance;
}
