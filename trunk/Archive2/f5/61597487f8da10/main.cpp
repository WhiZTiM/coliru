#include <iostream>
#include <map>
#include <numeric>
#include <iterator>
#include <functional>
#include <boost/iterator/transform_iterator.hpp>

int main()
{
    std::map<int, int> floor_plan;
    floor_plan[0] = 1;
    floor_plan[1] = 2;
            
    const size_t distance = std::accumulate(boost::make_transform_iterator(std::begin(floor_plan), std::mem_fn(&std::map<int, int>::value_type::second))
                                          , boost::make_transform_iterator(std::end(floor_plan), std::mem_fn(&std::map<int, int>::value_type::second))
                                          , 0);
    
    std::cout << "Total: " << distance;
}
