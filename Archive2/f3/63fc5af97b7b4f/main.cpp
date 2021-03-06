#include <cstddef>
#include <iostream>
#include <list>
#include <numeric>

bool predicate(int x) {
    return x < 5;
}

template<class ForwardIterator, class T>
void iota(ForwardIterator first, ForwardIterator last, T value) {
    while(first != last) {
        *first++ = value;
        ++value;
    }
}

int main() {
    std::list<int> integers;
    for (int i = 0; i < 10; ++i) {
        // I want std::iota. :<
        for (int j = 0; j < 10; ++j) {
            integers.push_back(j);
        }
    }
    integers.remove_if(&predicate);
    for (std::list<int>::iterator it = integers.begin(); it != integers.end(); ++it) {
        std::cout << *it << '\n';
    }
    return 0;
}
