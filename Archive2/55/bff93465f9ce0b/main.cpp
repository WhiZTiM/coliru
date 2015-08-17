#include <type_traits>

int main()
{
    auto lambda = [] (char, double) -> int { return 0; };
    using signature = int(char, double);
    static_assert(std::is_assignable<signature*&, decltype(lambda)>::value, "!");
}
