#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

vector<int> parseInts(string str) {
    vector<int> ints;
	stringstream ss(str);
	char ch;
	int x = 0;
	int i = 0;
	do {
		ss >> x >> ch;
		ints[i] = x;
		++i;
	} while (x != 0);
	return ints;
}

int main() {
	string str;
	cin >> str;
	vector<int> integers = parseInts(str);
	for (unsigned int i = 0; i < integers.size(); i++) {
		cout << integers[i] << "\n";
	}

	return 0;
}
