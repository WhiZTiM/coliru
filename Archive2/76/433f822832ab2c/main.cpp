#include <iostream>
#include <string>

int foo(int i)
{
    int res = 0;
    if (i % 2) {
        if (i % 3) {
            goto labelA;
        }
        // The lack of a goto here is a fallthrough bug case which should not happen.
    } else if (i % 3) {
        goto labelB;
    } else {
        goto labelC;
    }

    goto labelNoReturn; // -- this point should not be reached. --

labelA:
    res = 1;
    goto final;
labelB:
    res = 2;
    goto final;
labelC:
    res = 3;
    goto final;
final:
    return res;
labelNoReturn:
    {} 
}

int main() {
    foo(42);
}