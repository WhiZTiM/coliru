#include <boost/intrusive/set.hpp>
#include <boost/intrusive/set_hook.hpp>
#include <string>
#include <vector>
#include <functional>
#include <iostream>

namespace bive = boost::intrusive;

struct Element : bive::set_base_hook<> {
    std::string data;

    Element(std::string const& data = "") : data(data) {}

    bool operator< (Element const& rhs) const  { return data < rhs.data; }
    bool operator==(Element const& rhs) const  { return data ==rhs.data; }
};

using Set = bive::set<Element>;

template <typename Set>
void merge_into(Set& s, Set& into) {
    for (auto it = s.begin(); it != s.end();) {
        auto& e = *it;
        it = s.erase(it);
        into.insert(e);
    }
}

int main() {
    std::vector<Element> va {{"one"},{"two"},{"three"},{"four"},{"five"},{"six"},{"seven"},{"eight"}, {"nine"} };
    Set a;
    for(auto& v : va) a.insert(v);

    std::vector<Element> vb {{"two"},{"four"},{"six"},{"eight"}, {"ten"} };
    Set b;
    for(auto& v : vb) b.insert(v);

    assert(9==a.size());
    assert(5==b.size());

    merge_into(a, b);

    assert(a.empty());
    assert(10==b.size());
}
