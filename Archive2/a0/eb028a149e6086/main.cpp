 int main() {
    constexpr int a = 0;
    auto l = []() { return a; };

    return l();
}
