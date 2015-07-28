#include <vector>
#include <set>

template <typename T, template <typename...> class Base = std::vector>
class A : public Base<T>
{
};

int main()
{
    A<int> a;
    A<int, std::set> b;
}
