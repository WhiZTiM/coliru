#define FOO(x) foo(U ## #x, (x))

FOO(abc)