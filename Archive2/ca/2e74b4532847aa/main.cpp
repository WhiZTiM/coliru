#include <type_traits>

int main()
{
    using namespace std;

    auto x = [](int v){};
    void (*f)(int) = x;
    static_assert(is_class<decltype(x)>::value, "");
    static_assert(is_class<decltype(f)>::value, "");
}
