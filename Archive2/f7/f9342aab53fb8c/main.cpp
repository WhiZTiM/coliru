#include <iostream>
#include <vector>

using namespace std;

static int ent = 1;

class foo{
public:
	foo(){cout << ent++ << "construct" << endl;}
	foo(const foo& temp){cout << ent++ << "copy" << endl;}
	~foo(){cout << ent++ << "destruct" << endl;}
    foo& operator=(const foo& temp){cout << ent++ << "assign" << endl;}
    void func(){}
};

int main() {
	vector<foo> bar(2);
	
    bar[0].func();
    bar[1].func();
	cout << "resize4" << endl;
	ent = 1;
	bar.resize(4);
	cout << "resize1" << endl;
	ent = 1;
	bar.resize(1);
	cout << "resize3" << endl;
	ent = 1;
	bar.resize(3);
	
	return 0;
}