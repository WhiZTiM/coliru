#include <functional>
#include <memory>

int main()
{
    int i = 0;
    std::bind([](int&){}, std::move(i));
    std::bind([](int&&){}, std::move(i));
}