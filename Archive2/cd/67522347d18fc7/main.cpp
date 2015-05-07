#include <cstdio>
#include <cstdlib>
#include <clocale>

int main()
{
    char const * result = setlocale(LC_CTYPE, "en_US.UTF-8");
    if (result == NULL) {
        puts("Failed hard.");
        return 1;
    }
    char const * s = "£ > €";
    printf("%lu", mbstowcs(NULL, s, 0));
    return 0;
}