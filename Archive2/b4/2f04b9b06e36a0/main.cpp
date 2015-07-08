#include <type_traits>
using namespace std;
using X = int const&;
static_assert(is_same< remove_cv_t<X>, X>::value, "!");
static_assert(is_same< remove_cv_t<X>, int&>::value, "!");
int main();