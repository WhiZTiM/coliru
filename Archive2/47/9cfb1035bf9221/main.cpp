#include <boost/range/combine.hpp>

#include <iostream>
#include <vector>

int main()
{
    using namespace std;
    using namespace boost;
    
    std::vector<int> v{11, 22, 33};
    std::vector<char> w{'a', 'b', 'c'};
    
    for (auto e : boost::combine(v, w)) cout << e.get<0>() << " " << e.get<1>() << endl;
}

