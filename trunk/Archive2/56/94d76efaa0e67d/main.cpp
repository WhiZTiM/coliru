#include <tuple>
int test(std::tuple<int, int, int, int> tup) {
    return std::get<0>(tup) + std::get<1>(tup) + std::get<2>(tup) + std::get<3>(tup);
}
int test2(std::tuple<int, int, int, int> tup);
int main() {
    test2(std::make_tuple(1, 2, 3, 4)); 
}