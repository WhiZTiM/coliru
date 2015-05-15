#include <iostream>
using namespace std;

struct foo
{
    foo(int lol):lol(lol){}
	foo operator??-() { return {??-lol}; };
	int lol;
};

int main() {
	foo a{4};
	cout << a.lol << endl;
	cout << (??-a).lol << endl;
	return 0;
}