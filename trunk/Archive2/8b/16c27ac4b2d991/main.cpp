#include <iostream>
#include <vector>

using namespace std;
 
int foo(const vector<int> & vec)
{
    for (int val : vec)
		return val;

	return 0;
}

int main()
{
	vector<int> vec { 0, 1, 2, 3, 4, 5 };

	cout << foo(vec) << endl;

	return 0;
}