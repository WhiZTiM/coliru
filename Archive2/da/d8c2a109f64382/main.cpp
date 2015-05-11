class A
{
    int a = 5;
public:
    constexpr int f()
	{
		return 10/a;
	}

	constexpr int g()
	{
		a = 0;
		return 0;
	}

	constexpr int h(int a, int b)
	{
        return a;
	}

	constexpr int i()
	{
		return h(f(), g()); // Floating point exception(core dumped)
        //return h(g(), f()); // 0
	}
};

#include <iostream>
#include <array>

int main()
{
	A a;
	// std::array<int, a.i()> arr;
    std::cout << a.i();
    //constexpr int z = a.i();
}