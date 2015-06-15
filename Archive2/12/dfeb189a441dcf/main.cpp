#include <iostream>
#include <set>
#include <iterator>
#include <algorithm>

int main() {
    std::set<int> set {4, 2, 67, 7, 37, 26, -38, 82, -27};
    std::copy(begin(set), end(set), std::ostream_iterator<int>(std::cout, " "));
}