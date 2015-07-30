

struct A {
    A(float ) { } // (a)
    A(int ) { } // (b)
    A(double ) { } // (c)
};

int main() {
    A{1.1f}; // selects (a)
    A{1.1}; // selects (c), ambiguity error without (c)
}
