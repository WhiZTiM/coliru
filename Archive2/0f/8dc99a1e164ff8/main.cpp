#include <stdio.h>
#include <stdlib.h>

const char interp_path[] __attribute__((section(".interp"))) = "/lib64/ld-linux-x86-64.so.2";

struct startstack
{
    int argc;
    char *values[1];
};

struct stackframe
{
    void (*func)();
    struct startstack *st;
    void *res;
};

void hellolib(const char *name)
{
    printf("%s: Hello world!\n", name);
}

int __attribute__((visibility("internal"))) main( int argc, char **argv)
{
    hellolib(argv[0]);
}

void __attribute__((visibility("internal"))) start(void)
{
    struct stackframe sf;

    exit(main(sf.st->argc, sf.st->values));
}
