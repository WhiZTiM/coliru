#include <cstddef>

class Foo
{
public:
    explicit Foo(std::size_t) {}

private:
    Foo(const Foo&);
    void operator = (const Foo&);
};

int main()
{
    auto f = Foo(42);
}
