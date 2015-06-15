#include <iostream>
struct T
{
    T * operator *() { return this; }
	operator T * () { return this; }
	T * operator ~() { return this; }
};
void foo(T *) { std::cout << "wait, oh shi~~" << std::endl; }

int main()
{
	T bar;
	foo(&bar);
	foo(*bar);
	foo(bar);
	foo(~bar);
	return 0;
}
