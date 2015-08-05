#include <stdarg.h>
#include <string.h>
#include <typeinfo>
#include <iostream>
#include <memory>
#include <string>

using namespace std;

string meow() { return "meow"; }

int main()
{
    /*const*/ string &r = meow();
	r.append(" to milk");
	cout << r << "\n";

	cout << "\njob done\n";
	return 0;
}