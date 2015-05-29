#include <cstdlib>

struct foo
{
    static constexpr auto bar1 = &std::rand;
	static constexpr auto bar2 = 42;
};

constexpr decltype(foo::bar1) foo::bar1;  // comment this line to compile on VS2015
constexpr decltype(foo::bar2) foo::bar2;

#include <iostream>
int main()
{
	std::cout << (void*)foo::bar1 << '\n';
	std::cout << foo::bar2 << '\n';
}
