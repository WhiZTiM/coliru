#include <cstdio>

namespace pai
{
    FILE* fopen(const char* a, const char* b)
    {
        return std::fopen(a, b);
    }
}

using pai::fopen;

int main()
{
}
