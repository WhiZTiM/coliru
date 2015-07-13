#include <functional>

int main() {
    std::function<int(int)> f;
    bool b = true;
    f = b ? [](int a) { return 2*a; } : nullptr;
    return 0;
}