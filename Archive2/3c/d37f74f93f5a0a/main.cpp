#include <iostream>
#include <cstdlib>
#include <exception>
#include <stdexcept>

using namespace std;

void f(int n) throw (int) { throw (float)n; }
void g(int n) throw (float) { throw n; }

void onExit() {
    cout << "onExit" << endl;
}

void onTerminate() {
	cout << "onTerminate" << endl;
	exit(EXIT_FAILURE);
}
void onUnexpected() {
	cout << "onUnexpected" << endl;
	throw -1;
}

int main() {

        atexit(onExit);
	set_terminate(onTerminate);
	set_unexpected(onUnexpected);

	int n = 1;

	try { g(n); }
	catch (int n) { cout << "catch 1" << endl; }
	catch (...) { cout << "catch 2" << endl; }

	cout << "end main" << endl;
	return EXIT_SUCCESS;
}