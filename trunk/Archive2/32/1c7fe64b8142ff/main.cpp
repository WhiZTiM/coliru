struct S {
    constexpr int f() const { return 1; }  
};

int main() {
    static constexpr S s{};
    const S * const sp = &s;
    constexpr int i = sp->f(); // error: sp not a constant expression
}