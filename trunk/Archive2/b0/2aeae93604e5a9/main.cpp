struct X { virtual void f() = 0; };
struct Impl: virtual X { void f() {} };

struct Base: virtual X {};
struct Derived: Base, Impl {};

auto main() -> int
{
    Derived o;      // Absolutely not abstract.
}
