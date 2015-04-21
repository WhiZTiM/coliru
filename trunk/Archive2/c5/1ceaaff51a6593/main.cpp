#include <string>
#include <iostream>

struct V{
    int x;
    std::string y;
    float z;
};

template <typename Callable, typename... Vs>
V for_each_v (Callable c, const Vs&... vs)
{
    V v;
    v.x = c (vs.x...);
    v.y = c (vs.y...);
    v.z = c (vs.z...);
    return v;
}

int main ()
{
    V v1 {1, "two", 3.0};
    V v2 {4, "five", 6.0};
    auto vplus = for_each_v ([] (auto lhs, auto rhs) { return lhs+rhs; },
                             v1, v2);
    std::cout << vplus.x << ' ' << vplus.y << ' ' << vplus.z << std::endl;
}
