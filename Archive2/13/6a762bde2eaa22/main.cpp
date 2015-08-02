struct S {
    S()=default;
};

int main() {
    constexpr S s = S();
}