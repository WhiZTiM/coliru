#include <type_traits>

int main()
{
    using namespace std;

    auto x = [](int v){};
    void (*fp)(int) = x;
    static_assert(is_class<decltype(x)>::value, "");
    static_assert(is_class<decltype(fp)>::value, "");
}
