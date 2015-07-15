#include <algorithm>
#include <iostream>
#include <utility>

template<typename Class, typename Member>
auto by(const Member Class::*member) {
    return [=](const Class &lhs, const Class &rhs) {
        return lhs.*member < rhs.*member;
    };
}

int main() {
    using std::begin;
    using std::end;
    
    std::pair<int, int> pairs[]{
        {1, 6}, {5, 2}, {3, 4}
    };
    
    std::sort(begin(pairs), end(pairs), by(&std::pair<int, int>::second));
    
    for (const auto &p : pairs) {
        std::cout << p.first << ", " << p.second << '\n';
    }
}