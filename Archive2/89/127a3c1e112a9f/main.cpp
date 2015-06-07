#include <vector>

namespace A
{
    class a
    {
    };
}

namespace B
{
    A::a test; //Error: namespace "B::A" has no member class "a"
    ::A::a test2; //No error
    std::vector<int> test3; //Error: namespace "B::std" has no member "vector"
    ::std::vector<int> test4; //No error
}

int main() {}
