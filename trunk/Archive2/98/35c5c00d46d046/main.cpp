#include <vector>

struct Bar;

struct Foo
{
    using BarVec = std::vector<Bar>::size_type;
};

int main()
{
   Foo f;
}