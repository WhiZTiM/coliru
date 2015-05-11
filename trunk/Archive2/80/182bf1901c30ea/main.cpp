#include <typeinfo>
#include <stdexcept>

struct B { virtual ~B() noexcept = default; };
struct D : B { void f() {} };

void f(B& x) {
    if (auto* y = dynamic_cast<D*>(&x)) {
        y->f();
    }
}

int main() {
    B b;
    D d;
    f(b);
    f(d);
}