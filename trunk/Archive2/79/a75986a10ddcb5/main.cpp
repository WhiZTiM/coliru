constexpr int min(int x, int y) {
    return x < y ? x : y;
}

int main() {
    static_assert(min(5, 7) == 5);   
}