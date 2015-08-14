#include <iostream>
using namespace std;

class A {
public:
    int i;
	A(int i): i(i) {}
};

class B
{
    public:
    int i;
	B(int i): i(i) {}
    operator A()
    {
        std::cout << i << " is evaluated\n";
        return A(i);
    }
};


A operator* (const A& a, const A& b) {
	cout << "multiplication done\n";
	return A(a.i*b.i);
}

A operator/ (const A& a, const A& b) {
	cout << "division done\n";
	
	return A(a.i/b.i);
}
A operator+ (const A& a, const A& b) {
	return A(a.i + b.i);
}

ostream& operator<< (ostream& os, const A& a) {
	return os << a.i;
}

int main() {
	B a(3), b(4), c(2);
	cout << (a * b / c) << endl;
}
