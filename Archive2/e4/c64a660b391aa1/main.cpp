#include <iostream>

using namespace std;

int main()
{
    unsigned short x = 65535; // largest 16-bit unsigned value possible
    cout << "x was: " << x << endl;
    x = x + 1; // 65536 is out of our range -- we get overflow because x can't hold 17 bits
    cout << "x is now: " << x << endl;
    x = 65500;
    cout<<"byte size "<<sizeof(int);
        for(int i = x; i<65538; ++i) {
		    ++x;
    	    cout << x << " ";
    }
}