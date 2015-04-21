#include <initializer_list>
#include <vector>

struct test
{
    using t = std::vector<test>;
    test(t const &v)
	{
	}
	test(t &&v)
	{
	}
	test(std::initializer_list<test> v)
	: test{t{v}}
	{
	}
};

int main()
{
}
