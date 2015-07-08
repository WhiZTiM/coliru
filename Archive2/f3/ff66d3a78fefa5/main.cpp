#include <iostream>

class Foo
{
    struct Bar
	{
		void pr(){ std::cout << "asd"; }
	};

public:
	Bar GetBar() { return Bar(); }
};

int main()
{
	Foo f;
	//Foo::Bar b = f.GetBar();
	auto b = f.GetBar();

	b.pr();
}