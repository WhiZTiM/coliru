#include <cassert>
#include <utility>
#include <vector>

template<typename T, std::size_t... Is, typename... Ts>
void assign_multiple_helper(std::vector<T> &vec, std::index_sequence<Is...>, Ts... val) {
    [](...){}((vec[Is] = val)...);
}    

template<typename T, typename... Ts>
void assign_multiple(std::vector<T> &result, Ts... args) {
    result.resize(sizeof...(Ts));
    assign_multiple_helper(result, std::index_sequence_for<Ts...>{}, args...);
}

int main() {
    std::vector<double> v;
    assign_multiple(v, 1.1, 2.2, 3.3);
    assert(v.at(0) == 1.1);
    assert(v.at(1) == 2.2);
    assert(v.at(2) == 3.3);
}
