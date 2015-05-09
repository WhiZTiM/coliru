#include <type_traits>
#include <iostream>
 
double f(double x)
{
    return x;
}

int f(int x)
{
    return x;
}

int main()
{
    {
		using result_type = std::result_of<decltype(&f)(int)>::type;
		static_assert(std::is_same<result_type, int>::value, "");
	}
}
