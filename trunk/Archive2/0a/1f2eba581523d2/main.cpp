constexpr int f(const int *p) { return 1; }

int main() {
    /*constexpr*/ int *const ip = nullptr;
    constexpr int i = f(ip);
}