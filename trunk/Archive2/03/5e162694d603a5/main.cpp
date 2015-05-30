#include <type_traits>

typedef int& INTREF;

int main()
{
    static_assert(std::is_same<const INTREF, int&>{}, "!");
}