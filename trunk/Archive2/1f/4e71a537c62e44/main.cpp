#include <iostream>
#include <functional>
#include <map>

namespace streaming {

    template <typename T>
    struct tag : std::reference_wrapper<T> {
        using std::reference_wrapper<T>::reference_wrapper;
    };

    using tag_ostream = tag<std::ostream>;

    template <typename T1, typename T2>
    static inline tag_ostream operator<<(tag_ostream os, std::pair<T1, T2> const& p) {
        os.get() << "std::pair{" << p.first << ", " << p.second  << "}";
        return os;
    }

    template <typename Other>
    static inline tag_ostream operator<<(tag_ostream os, Other const& o) {
        os.get() << o;
        return os;
    }
}

int main() {
    std::map<int, std::string> standback { { 42, "I'm gonna try" }, { 1729, "science" } };

    streaming::tag_ostream out = std::cout;

    for (auto& entry : standback)
        out << entry << "\n";
}
