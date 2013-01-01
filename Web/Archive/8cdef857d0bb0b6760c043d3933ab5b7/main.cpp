// vector::emplace
#include <iostream>
#include <vector>
#include <utility>

template <typename Args>
const Args& eat_none(const Args& args)
{
    std::cout << "sizeof args:" << sizeof(args) << std::endl;
    return args;
}

template <typename T>
unsigned int print_helper(unsigned int n, const T& val)
{    
    std::cout << n << ": =" << val << std::endl;
    return n;
}

template <typename T, typename... Args>
void print_helper(unsigned int n, const T& val, const Args&... args)
{
    std::cout << n << ": =" << val << std::endl;
    print_helper(++n, args...);
}

template <typename... Args>
void TestVariadic(const Args&... args)
{
    print_helper(0, eat_none<Args>(args)...);
}

int main ()
{
  int p = 5;
  TestVariadic(4, 'a', p);

  return 0;
}