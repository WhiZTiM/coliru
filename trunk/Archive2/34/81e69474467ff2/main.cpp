#include <boost/fusion/include/copy.hpp>
#include <boost/fusion/include/vector.hpp>
#include <boost/fusion/adapted/boost_array.hpp>
#include <boost/array.hpp>

using namespace boost;

#include <iostream>
int main() {
    fusion::vector<int, int, int> fv(1,2,3);
    array<int, 3> arr;
    
    fusion::copy(fv, arr);

    for(auto i : arr)
        std::cout << i << " ";
}
