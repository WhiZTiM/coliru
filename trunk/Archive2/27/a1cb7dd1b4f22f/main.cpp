struct B {};

struct D: private B {
    void f() {
        B& b = *this; // ok
    }
    friend void g();
};

void g() {
    B& b = *new D; // ok
}

int main() {
    B& b = *new D; // error
}