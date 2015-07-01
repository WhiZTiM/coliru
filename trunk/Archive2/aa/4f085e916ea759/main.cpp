#include <boost/icl/interval_set.hpp>
#include <iostream>

using Set      = boost::icl::interval_set<int>;
using Interval = Set::interval_type;

int main() {

    Set record;

    // pool Group A - returns 1, 4
    // pool Group B - returns 2, 3
    // pool Group A - returns 6
    // pool Group B - returns 5

    int stepcount = 0;

    for (int sample : {
            1, 4,
            2, 3,
            6,
            5 })
    {
        record.insert(Interval::right_open(sample, sample+1));
        std::cout << "state at #" << ++stepcount << ": " << record << "\n";
    }
}
