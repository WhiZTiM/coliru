#include <type_traits>

int main() {
    using T = int[5];
    using U = T[3];
    static_assert(std::is_same<U, int[3][5]>::value, "arrays are not the same");
}