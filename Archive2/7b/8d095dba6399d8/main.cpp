#include <iostream>
#include <string>
#include <vector>
#include <forward_list>
#include <list>
#include <algorithm>
#include <utility>
#include <functional>

template<typename BiDirIt, typename Compare = std::less<>>
void bubble_sort(BiDirIt first, BiDirIt last, Compare cmp = Compare{}) {
    for (; first != last; --last) {
        auto sorted_begin = first;
        for (;;) {
            auto sorted_end = std::is_sorted_until(sorted_begin, last, cmp);
            if (sorted_end == last) break;
            auto prev = std::prev(sorted_end);
            sorted_begin = std::upper_bound(sorted_end, last, *prev, cmp);
            std::rotate(prev, sorted_end, sorted_begin);
        }
    }
}

template<typename T, typename BidirIt, typename Compare = std::less<>>
void radix_msb_sort_helper(T mask, const Compare& cmp, BidirIt first, BidirIt last) {    
    if (first == last) return;
    auto mid = std::partition(first, last, [&](const T& x){ return ((x & mask) != 0) ^ cmp(0, 1); });
    mask >>= 1;
    if (!mask) return;
    radix_msb_sort_helper(mask, cmp, first, mid);
    radix_msb_sort_helper(mask, cmp, mid, last);
}

template<typename It, typename Compare = std::less<>>
void radix_msb_sort(It first, It last, Compare cmp = Compare{}) {    
    using value_type = decltype(+*first);
    auto max_value = ~static_cast<value_type>(0);
    radix_msb_sort_helper(max_value ^ (max_value >> 1), cmp, first, last);
}

int main() {
    using value_type = unsigned;
    std::vector<std::vector<value_type>> test_set = {
        {1},
        {1,2,3,2,1,4},
        {4,3,2,1},
        {1,2,3},
        {3,2,1},
        {1,2,1},
        {2,1,2},
    };

    std::greater<> cmp;
    //std::less<> cmp;
    using cont_t = std::vector<value_type>;

    for (auto&& test : test_set) {
        cont_t cont(test.begin(), test.end());
        
        radix_msb_sort(cont.begin(), cont.end(), cmp);
    
        if (!std::is_sorted(cont.begin(), cont.end(), cmp)) {
            for (auto x : test) std::cout << x << ' ';
            std::cout << "FAILED: ";
            for (auto x : cont) std::cout << x << ' ';
            std::cout << "FAILED\n";
        }
    }
    std::cout << "done\n";
}

