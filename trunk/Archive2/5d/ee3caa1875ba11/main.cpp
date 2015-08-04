#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
#include <utility>

int main() {
	std::vector<int> vec = {0, 1, 2, 3, 4, 5, 6};
    auto foundit = std::find_if(vec.begin(), vec.end(), [](int n) -> bool { return n==5; });

    if ( foundit != vec.end() ) {
        typedef std::reverse_iterator<decltype(foundit)> RevIt;
        RevIt rit(foundit);
        RevIt rend(vec.begin());
        for ( ; rit != rend; ++rit ) {
            std::cout << *rit << std::endl;
        }
    }
}