#include <utility>
#include <vector>
#include <algorithm>
#include <iostream>

template <class F>
struct negate {
    negate(F&& f)
    : _f(std::forward<F>(f)) {}
    
    template <class... Args>
    bool operator () (Args &&... args) {
        return !_f(std::forward<Args>(args)...);
    }
    
private:
    F _f;
};

template <typename Container, typename Filter>
void filter_ip(Container& c, Filter&& f)
{
    c.erase(std::remove_if(
        c.begin(),
        c.end(),
        negate<Filter>(std::forward<Filter>(f))),
        c.end()
    );
}

int main() {
    std::vector<int> v {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    filter_ip(v, [](int i) {return bool(i%2);});
    for(auto &&i : v)
        std::cout << i << ' ';
    std::cout << '\n';
}
