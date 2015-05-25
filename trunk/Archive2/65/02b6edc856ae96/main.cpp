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
 void quicksort1(ForwardIt first, ForwardIt last)
 {
    if(first == last) return;
    auto pivot = *std::next(first, std::distance(first,last)/2);
    ForwardIt middle1 = std::partition(first, last,
                         [pivot](const auto& em){ return em < pivot; });
    ForwardIt middle2 = std::partition(middle1, last,
                         [pivot](const auto& em){ return !(pivot < em); });
    quicksort1(first, middle1);
    quicksort1(middle2, last);
 }
 
 template <class ForwardIt>
 void quicksort2(ForwardIt first, ForwardIt last)
 {
    if(first == last) return;
    auto pivot = *first;
    ForwardIt middle = std::partition(first, last,
                         [pivot](const auto& em){ return em <= pivot; });
    //print_range(first, middle);
    quicksort2(first, middle);
    quicksort2(std::next(middle), last);
 }

int main() {
    std::vector<int> vec1 { 1, 55, 12, 23, 123, -387, 0, 23 };
    std::vector<int> vec2 { 1, 55, 12, 23, 123, -387, 0, 23 };
    std::list<int> lst1 { 1, 55, 12, 23, 123, -387, 0, 23 };
    std::list<int> lst2 { 1, 55, 12, 23, 123, -387, 0, 23 };
    quicksort1(vec1.begin(), vec1.end());
    quicksort2(vec2.begin(), vec2.end());
    quicksort1(lst1.begin(), lst1.end());
    //quicksort2(lst2.begin(), lst2.end());
    print_range(vec1.begin(), vec1.end());
    print_range(vec2.begin(), vec2.end());
    print_range(lst1.begin(), lst1.end());
    print_range(lst2.begin(), lst2.end());
}
