#include <iostream>

struct thing {
    void stuff() {}
};

struct other {
	int bla() { return 1; }
};

int main() {
	std::cout << &thing::stuff << "\n";
	std::cout << &other::bla << "\n";
	//std::cout << (&thing::stuff == &other::bla) << "\n"; //not even MSVC lets me compare them
}
