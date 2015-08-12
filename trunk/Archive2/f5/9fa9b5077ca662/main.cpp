#include <iostream>

template<class T>
struct Foo
{
    Foo(T v) : m_value(v){}
	~Foo() { m_value.~T(); }
	T m_value;
};
 
int main() {
	Foo<int>(10);
    int a;
    std::cout << "fads" << std::endl;
    a.~int();
	return 0;
}