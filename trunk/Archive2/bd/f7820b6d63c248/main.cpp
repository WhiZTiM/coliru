#include <iostream>
using namespace std;
class A {
public:
    int i;
	A(int i): i(i) {}
};
A operator* (A& a,A& b) {
	cout << "multiplication done\n";
	return A(a.i*b.i);
}
A operator/ (A& a, A& b) {
	cout << "division done\n";
	return A(a.i/b.i);
}
A operator+ (A& a, A& b) {
	cout << "addition done\n";
	return A(a.i + b.i);
}
A operator- (A& a, A& b) {
	cout << "subtraction done\n";
	return A(a.i - b.i);
}
int main() {
	A a(4), b(2);
	cout << (a*b).i << (a+b).i << (a/b).i << (a-b).i << endl;
    return 0;
}