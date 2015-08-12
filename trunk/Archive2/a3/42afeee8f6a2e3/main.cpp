
constexpr int ceil(float num) {
    int inum = static_cast<int>(num);
    if (num == static_cast<float>(inum)) {
        return inum;
    }
    return inum + (num > 0 ? 1 : 0);
}

static_assert(42 == ceil(42.f), "unexpected result");
static_assert(0 == ceil(0.f), "unexpected result");
static_assert(5 == ceil(4.2f), "unexpected result");
static_assert(-4 == ceil(-4.2f), "unexpected result");

int main() {
}
