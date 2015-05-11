#include <typeinfo>
#include <stdexcept>

struct B { virtual ~B() noexcept = default; };
struct D : B { void f() { throw std::runtime_error(""); } };

void f(B& x) {
    try { dynamic_cast<D&>(x).f(); }
    catch (std::bad_cast const&) {}
}

int main() {
    B b;
    D d;
    f(b);
    f(d);
}