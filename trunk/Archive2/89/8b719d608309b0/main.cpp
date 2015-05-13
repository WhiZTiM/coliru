#include <type_traits>

struct Array1 {
    using arr_t = int[3];
};

struct Array2 {
    using arr_t = Array1::arr_t[2];
};

static_assert(std::is_same<Array2::arr_t, int[2][3]>::value, "");

int main() {}