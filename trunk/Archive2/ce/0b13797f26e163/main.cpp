#include <type_traits>
#include <tuple>

int main() {
    bool b = std::is_convertible<std::tuple<int&&>, std::tuple<int const&>>::value;
    (void)b;
}
