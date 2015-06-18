#include <iostream>
using namespace std;

struct A { int a; };
struct B { int b; };

class C : public A, public B
{
    int c;
};

int main() {
	C * volatile c = 0;
	B * volatile b = c;
	
	std::cout << (b == 0) << std::endl;
	
	return 0;
}