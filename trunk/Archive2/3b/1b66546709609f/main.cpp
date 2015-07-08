#include <stdio.h>

struct A
{
    int a;
    int b;
    A(int _a, int _b) : a(_a), b(_b) {};
};

struct B
{
    int a;
    int b;
};

template <typename T> void fn(T* in)
{
    printf("a = %i, b = %i\n", in->a, in->b);
}

int main()
{
    fn(&A{ 1, 2 });      //OK, no extra magick
    /*  fn(&B {3, 4});      //error: expression must be an lvalue or function designator */
    fn(&(B)B{ 3, 4 });  //OK with explicit cast to B (but why?)
}