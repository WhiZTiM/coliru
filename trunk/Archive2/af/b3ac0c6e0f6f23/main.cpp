void segfault() { volatile int x[100000000000000]; (void)x; }

int main() {
    segfault();
}