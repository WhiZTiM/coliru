#include <iostream>
#include <string>
using namespace std;
string value1() { cout << "value1\n"; return "value1\n"; }
string value2() { cout << "value2\n"; return "value2\n"; }
string value3() { cout << "value3\n"; return "value3\n"; }
int main() {
cout << value1() << value2() << value3();
return 0;}