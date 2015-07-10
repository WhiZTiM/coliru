#include <string>
#include <cstdarg>
#include <cstdio>

__attribute__ ((format (printf, 1, 2)))
std::string astringprintf(const char* s, ...)
{
    va_list vl;
    va_start(vl, s);
    char* strp;
    vasprintf(&strp, s, vl);
    std::string res = strp;
    free(strp);
    va_end(vl);
    return res;
}

int main() {
    auto s2 = astringprintf("%f", "test");
}