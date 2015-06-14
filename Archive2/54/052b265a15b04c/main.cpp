#include <memory>

#include <memory>
#include <array>
struct Bob
{ 
    explicit Bob(){};
};
void f(std::array<int, 1>) {}
void f(Bob) {}

int main()
{
    f({});
}