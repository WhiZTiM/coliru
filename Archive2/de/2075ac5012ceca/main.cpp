#include <stdio.h>

int main(int argc, char* argv[]) {
    printf("sizeof(char*)=%i, argc=%i, sizeof argv=%i\n\n", (int)sizeof(char*), argc, (int)sizeof argv);
}