struct test {
    template<typename... Args>
    test(Args&&...) {}
};

int main() {
    test x = { 1, 2, 3, 4, 5 }; // no std::initializer_list here
    (void)x;
}