void f() {}

constexpr void (*gibe_f())() { return &f; }

template<void (*F)()> struct carrier;

using business_as_usual = carrier<&f>;
using lol = carrier<gibe_f()>;

int main()
{
}
