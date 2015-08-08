#include <iostream>
using namespace std;
int main()
{
    unsigned char al = 'Alex';
	unsigned char lp;
	cout << "What is your name?";
	cin >> lp;
	if(lp == al)
	{
		cout << "Hi Alex" << endl;
	}
	else
	{
		cout << "Not Alex" << endl;


	}
	return 0;




}