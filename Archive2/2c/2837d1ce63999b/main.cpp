#include <tuple>

template<typename T>
auto sumFirst(T const& t) -> decltype(get<0>(t) + get<1>(t)) { return get<0>(t) + get<1>(t); }

namespace my_project {
    template< typename >
    void get() = delete;

    std::tuple< int > blah;
    int q = sumFirst(blah);
}

int main() {}