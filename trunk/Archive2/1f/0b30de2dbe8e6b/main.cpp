#include <iostream>
using std::cout;
using std::endl;

template <typename T> struct vec2 {
    T x;
	T y;

	vec2(vec2<T> original):
		x(original.x),
		y(original.y)
	{}
};

int main(int argc, char* argv[])
{
	vec2<int> foo;
	foo.x = 5;
	foo.y = 4;

	vec2<int> bar(foo);

	cout << "foo.x:\t" << foo.x << endl;
	cout << "foo.y:\t" << foo.y << endl;
	cout << endl;
	cout << "bar.x:\t" << bar.x << endl;
	cout << "bar.y:\t" << bar.y << endl;

	return 0;
}