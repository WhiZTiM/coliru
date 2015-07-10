#include <stdio.h>
#include <new>

struct Obj { Obj() { printf("%p\n", (void*)this); } };

int main() { new(0) Obj; }