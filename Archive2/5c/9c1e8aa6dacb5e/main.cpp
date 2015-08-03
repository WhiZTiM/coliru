#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include <iomanip>
using namespace std;

void print(int i)
{
	cout << setw(3) << setfill('0') << i << "\n";
	if (((i+1) % 50) == 0)
		i += 50;
    print(++i);
}


int main()
{
    print(0);
    return 0;
} 