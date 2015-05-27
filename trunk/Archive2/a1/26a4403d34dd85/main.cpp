#include <iostream>
#include <vector>

    template<typename It, typename OutIt, typename BinaryOp>
    void counting_sort(It first, It last, OutIt out, std::size_t k, BinaryOp index_for) {
        std::vector<std::size_t> tmp(k);
        for (auto it = first; it != last; ++it)
            tmp[index_for(*it)]++;
        for (auto it = next(begin(tmp)); it != end(tmp); ++it)
            *it = *(it - 1);
        for (auto it = last - 1; /* */; --it) {
            std::size_t& idx = tmp[index_for(*it)];
            *std::next(out, idx) = *it;
            idx--;
            if (it == first) break;
        }
    }


int main() {
    std::vector<int> vec { -4, 2, -5, 0, 0, 2, 1, 3, 4, -1, 5 };
    std::vector<int> out(11);
    auto index_fn = [](int i) { return i + 5; };
    counting_sort(begin(vec), end(vec), std::back_inserter(out), 11, index_fn);
    
    for (auto i : out)
        std::cout << i << ' ';
    std::cout << '\n';
}
