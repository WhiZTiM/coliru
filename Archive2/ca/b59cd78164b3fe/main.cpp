
#include <iostream>
using namespace std;

int (*foo)();
int (*foo2)(int);
int (*foo3)(char);

template<class T>
int test(T n){
    cout << n << endl;
}

int main(int argc, char *arg[]){

	foo2=&test;
	foo3=&test;

	foo2(2);
	foo3('a');

	return 0;
}