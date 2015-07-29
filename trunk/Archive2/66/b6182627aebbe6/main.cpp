#include <iostream>
#include <sstream>
using namespace std;

int main() {
    istringstream foo("lorem ipsum");
	
	cout << foo.rdbuf()->in_avail();
	return 0;
}