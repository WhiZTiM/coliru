#include <cstdio>
#include <utility>

template <typename T>
void test(T const & t)
{
  puts(__PRETTY_FUNCTION__);
}

template <typename ...Args>
void foo()
{
    auto f = std::index_sequence_for<Args...>();
    test(f);
}

int main()
{
     foo<int, float, char>();
}
