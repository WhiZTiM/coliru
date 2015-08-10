#include <iostream>
#include <utility>
#include <string>

template <int> struct idx_ {};

template <int I>
idx_<I> idx;

template <class T1, class T2>
class myPair {
    std::pair<T1, T2> member;
public:
    myPair() = default;
    myPair(T1 x, T2 y) : member(std::make_pair(x, y)) {}
    
    T1 &operator [] (idx_<0>) {
        return member.first;
    }
    
    T2 &operator [] (idx_<1>) {
        return member.second;
    }
};

int main() {
    myPair<int, std::string> mp(42, "Hi");
    std::cout << mp[idx<0>] << ", " << mp[idx<1>] << '\n';
}