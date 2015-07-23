#include <iostream>

template<typename T>
using alias = T;

template<typename T>
struct wtf {
    T storage[3] = { };

	operator alias<T[3]>& () { return storage; }
};

int main() {

	wtf<void*> x;
	x++;

	std::cout << x.storage[0] << "\n";
}