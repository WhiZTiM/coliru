#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include <iomanip>
using namespace std;

void print()
{
	for (int i = 0; i < 950; i++)
	{
		cout << setw(3) << setfill('0') << i << "\n";
		if (((i+1) % 50) == 0)
			i += 50;
	}
}


int main()
{
    print();
    return 0;
} 