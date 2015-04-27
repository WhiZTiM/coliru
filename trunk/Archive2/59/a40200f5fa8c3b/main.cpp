struct C {
    static const auto X = 1;
};

int f(const int& arg) {
    return arg;
}

int main() {
    return f(C::X);
}