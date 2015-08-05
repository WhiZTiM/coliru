#include <algorithm>
#include <stdint.h>

using u64 = uint64_t;


u64 min(u64 a, u64 b)
{
    return std::min(a, b);
}

u64 min(u64 x, u64 y, u64 z)
{
    return min(min(x, y), z);
}

u64 min(u64 a, u64 b, u64 c, u64 d)
{
    return min(min(a, b), min(c, d));
}

u64 min(u64 a, u64 b, u64 c, u64 d, u64 e)
{
    return min(min(a, b), min(c, d), e);
}

u64 min(u64 a, u64 b, u64 c, u64 d, u64 e, u64 f)
{
    return min(min(a, b), min(c, d), min(e, f));
}

u64 min(u64 a, u64 b, u64 c, u64 d, u64 e, u64 f, u64 g)
{
    return min(min(a, b), min(c, d), min(e, f, g));
}

u64 min(u64 a, u64 b, u64 c, u64 d, u64 e, u64 f, u64 g, u64 h)
{
    return min(min(min(a, b), min(c, d)), min(min(e, f), min(g, h)));
}

u64 min(u64 a, u64 b, u64 c, u64 d, u64 e, u64 f, u64 g, u64 h, u64 i, u64 j)
{
    return min(min(min(min(a, b), min(c, d)), min(min(e, f), min(g, h))), min(i, j));
}

u64 min(u64 a, u64 b, u64 c, u64 d, u64 e, u64 f, u64 g, u64 h, u64 i, u64 j, u64 k, u64 l)
{
    return min(
        min(a, b, c, d),
        min(e, f, g, h),
        min(i, j));
}

u64 min(u64 a, u64 b, u64 c, u64 d, u64 e, u64 f, u64 g, u64 h, u64 i, u64 j, u64 k, u64 l, u64 m, u64 n)
{
    return min(
        min(a, b, c, d),
        min(e, f, g, h),
        min(i, j, k, l));
}

u64 min(u64 a, u64 b, u64 c, u64 d, u64 e, u64 f, double g, double h, double i, double j, double k, double l)
{
    return min(
        min(a, b, c, d, e, f),
        u64(
            std::min(
                std::min(std::min(g, h), std::min(i, j)),
                std::min(k, l))));
}

