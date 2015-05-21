typedef struct _A{
    unsigned int a;
}A;
const A a = {9} ; const A b = { .a = 10 }; const A c = {0};

typedef struct _Z{
    A a;
    A b;
    A c;
}Z;
Z z = { a,b,c };