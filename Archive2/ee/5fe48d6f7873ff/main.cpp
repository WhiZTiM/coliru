#include <iostream>
using namespace std;
 
int main() {
    auto func = [] () {
		int intNum = 0;
		cin >> intNum;
		while (intNum != 42) {
			cout << intNum << "\n";
			cin >> intNum;
		}
	};
	func();
 
	return 0;
}