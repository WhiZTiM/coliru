//evaluation order for call via function pointer
//output: get bar get baq 
// absence of bax in the output indicated that
// expression (*foo) is evaluated before expresion get()
#include <iostream>

void bar(int);
typedef void (*func)(int);
func foo = bar;

void baq(int) {
    foo = nullptr;
	std::cout << "baq ";
}

void bar(int) {
	foo = baq;
	std::cout << "bar ";
}

void bax(int) {
	foo = baq;
	std::cout << "bax ";
}

int get() {
	foo = bax;
	std::cout << "get ";
	return 0;
}


int main(int, char**) {
	while( foo ) (*foo)(get());
	return 0;
}
