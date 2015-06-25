#include <cstdio>
#include <cstdlib>

struct site{
    char name[20] = { 0 };
    int no_of_pages = 7;
};


int main()
{
    struct site a;
    printf("%d `%c`", a.no_of_pages, a.name[0]);
    return 0;
}
