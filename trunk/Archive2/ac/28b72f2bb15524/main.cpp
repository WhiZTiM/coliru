#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
 
 template<typename It>
void print_range(It begin, It end) {
    for (auto it = begin; it != end; ++it)
        std::cout << *it << ' ';
    std::cout << '\n';
}
 
 template <class ForwardIt>
 void quicksort2(ForwardIt first, ForwardIt last)
 {
    if(first == last) return;
    auto pivot = *first;
    ForwardIt middle = std::partition(first, last,
                         [pivot](const auto& em){ return em <= pivot; });
    print_range(first, middle);
    print_range(std::next(middle), last);
    quicksort2(first, middle);
    quicksort2(std::next(middle), last);
 }

int main() {
    std::vector<int> vec1 { 1, 55, 12, 23, 123, -387, 0, 23 };
    print_range(vec1.begin(), vec1.end());
    quicksort2(vec1.begin(), vec1.end());
}
