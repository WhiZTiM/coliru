#include <cstddef>

void foo(std::nullptr_t) = delete;
void foo(int*) {}

int main()
{
    foo(NULL);
}
