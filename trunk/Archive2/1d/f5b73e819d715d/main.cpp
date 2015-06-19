#include <iostream>
using namespace std;

class A
{
public:
    virtual void f(){
		cout << 'a' << endl;
	}

	virtual void h(){
		cout << 'A' << endl;
	}
};

class S1 : public A
{
public:
	virtual void f(){
		cout << "s1" << endl;
	}
};

class S2: public A
{
public:
	void h(){
		cout << "s2" << endl;
	}
};

class GS: public S1, public S2
{
};

int main(){
	/*GS gs;
	gs.f();*/

	S1 *q = new GS;
	q->h();
	return 1;
}