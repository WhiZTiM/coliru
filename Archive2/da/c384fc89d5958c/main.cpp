#include <string>
#include <iostream>
using namespace std;

typedef unsigned long ulong;
typedef unsigned int uint;
typedef unsigned short uint16;
typedef unsigned char uchar;

int main(int argc, char *argv[]) {
    string s = "h\x8fllo world";
    printf("%d\n", s[1]);
    if (s[1] =='\x8f') {
        printf("yes\n");
    }
    return 0;
}