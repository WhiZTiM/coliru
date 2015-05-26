#include <initializer_list>

int main()
{
    auto const x = { 0 };
    std::initializer_list<int> y = x;
}
