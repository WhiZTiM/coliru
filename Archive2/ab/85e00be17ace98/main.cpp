#include <algorithm>
#include <iostream>

class range_iter {
private:
    int val;
public:
    range_iter(int val) : val(val)
    { }
    
    int operator*() const { return val; }
    range_iter& operator++() { ++val; return *this; }
    range_iter operator++(int) { auto tmp = *this; operator++(); return tmp; }
    bool operator==(const range_iter& other) const { return val == other.val; }
    bool operator!=(const range_iter& other) const { return !operator==(other); }
};

template<typename InputIt, typename T, typename Pred>
T sum_if(InputIt first, InputIt last, T init, Pred pred) {
    return std::accumulate(first, last, init, [=](const T& val, const T& delta) {
        return pred(delta) ? val + delta : val;
    });
}

int main() {
    int sum = sum_if(range_iter{0}, range_iter{1000}, 0, [](int x) {
        return x % 3 == 0 || x % 5 == 0; 
    });
    std::cout << sum << '\n';
}
