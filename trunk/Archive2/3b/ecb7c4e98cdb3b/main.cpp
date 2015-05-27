#include <iostream>
using namespace std;

struct Int
{
    Int& operator=(int) { return *this; }
    explicit operator bool() { return false; }
};


int main() {
    

    Int i;
    
    cout << boolalpha << static_cast<bool>(i=2) << endl;

	// your code goes here
	return 0;
}