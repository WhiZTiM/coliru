#include <cstdlib>

namespace ns {
    struct foo
	{
		static constexpr auto bar1 = &std::rand;
		static constexpr auto bar2 = 42;
	};
}

constexpr decltype(ns::foo::bar1) ns::foo::bar1;
constexpr decltype(ns::foo::bar2) ns::foo::bar2;

int main()
{}
