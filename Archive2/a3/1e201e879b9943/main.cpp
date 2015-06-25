void f() {}

template<void (*F)()> struct carrier;

template<typename Type> using alias = Type;

struct quasi_closure {
    constexpr operator alias<void(*)()>() const { return &f; }
};

// okay
using A = carrier<&f>;

// also okay
constexpr void (*b)() = quasi_closure {};
static_assert( b == &f, "???" );

// not okay
using C = carrier<quasi_closure {}> {};

int main()
{
}
