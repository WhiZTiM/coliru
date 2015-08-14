#include <iostream>
#include <string>
using namespace std;
string value1() { cout << "value1 called\n"; return "value1 displayed\n"; }
string value2() { cout << "value2 called\n"; return "value2 displayed\n"; }
string value3() { cout << "value3 called\n"; return "value3 displayed\n"; }
int main() {
cout << value1() << value2() << value3();
return 0;}