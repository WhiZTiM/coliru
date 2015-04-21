#include <utility>

class my
{
    int a ()
	{
	}
	int b (int z)
	{
		(void)z;
	}
	template <class FuncPtr, typename... Args>
	int f (FuncPtr func,  my z, Args&&... FUNC_ARG)
	{
		(this->*func)(std::forward<Args>(FUNC_ARG)...);
	}
	int hren ();
};

int my::hren ()
{
	my z;
	f (&my::b, z, 1);
    f (&my::a, z);
}
int main ()
{
}