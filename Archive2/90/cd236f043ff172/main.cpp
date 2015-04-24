#define CONCAT2(x, y) x ## y
#define CONCAT(x, y) CONCAT2(x, y)
#define STRINGIZE(x) #x
#define FOO(x) foo(CONCAT(U, STRINGIZE(x)), (x))

FOO(abc)