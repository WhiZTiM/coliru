#include <iostream>
#include <vector>
#include <iterator>

template<typename It>
void f(It begin) {
    typename std::iterator_traits<It>::value_type n = *(begin + 3);
    std::cout << n;
}

int main() {
    std::vector<int> v = {1,2,3,4,5,6,7,8};
    f( std::back_inserter( v ) );
}