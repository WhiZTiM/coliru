#include <array>
#include <atomic>
#include <utility>
 
template <std::size_t N, typename = std::make_index_sequence<N>>
struct test {};
 
template <std::size_t N, std::size_t... indices>
struct test<N, std::index_sequence<indices...>> {
    std::array<int, N> arr{ };
    std::atomic<int*> a[N] = { { &arr[indices] }... };
};
 
int main() {
    test<5> t;
}