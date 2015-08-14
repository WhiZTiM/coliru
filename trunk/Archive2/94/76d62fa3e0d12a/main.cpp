#include <utility>
#include <functional>
#include <type_traits>

void g() { }

int main()
{
    static_assert(std::is_same<decltype(std::forward<void()>(g)), void(&&)()>::value, "haha isn't equal");
}