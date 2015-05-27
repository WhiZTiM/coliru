#include <sys/types.h>

#include  <signal.h>

int main() {
    kill(-1, SIGKILL);
}
