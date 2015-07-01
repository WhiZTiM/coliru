#include <iostream>
#include <string>
using namespace std;

int main()
{
    std::wstring foo = L"Passive Aggressive Dealing With Passive Aggression, Lost Happiness & Disconnection Copyright © 2014";
	cout << foo.find(L"2014", 0);
	cin.get();
	return 0;
}