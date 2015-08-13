#include <iostream>
#include <atomic>
#include <vector>
#include <signal.h>

std::vector<std::atomic<struct sigaction> > vec (1);

int main() {
    struct sigaction sa = { };
    vec[0].store (sa);
    sa = vec[0].load ();
    return 0;
}