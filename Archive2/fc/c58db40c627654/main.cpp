#include <iostream>

template<class T, int N>
void f(const T (&)[N])
{
}

int main() {
	f({1, 2, 3});
}
