class B { };
class D : public B { void f(); };

void f(B& x) {
    if (auto y = dynamic_cast<D*>(&x)) {
        y->f();
    }
}

int main() {
    B b;
    D d;
    f(b);
    f(d);
}