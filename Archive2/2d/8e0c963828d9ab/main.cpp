#include <iostream>
#include <functional>
using namespace std;
//==================== Interface class ================
class CallbackInterface {
public:
    virtual int doWork(int)=0;
};
class Callee0: public CallbackInterface {
public:
    int doWork(int i) {
		cout << "Callee::doWork() inside callback\n";
		return 2 * i;
	}
};
class Caller0 {
public:
	void connectCallback(CallbackInterface* cb) {
		this->m_cb = cb;
	}
	void test() {
		cout << "Caller::test() calling callback\n";
		int i = m_cb->doWork(10);
		cout << "Caller::test() result: " << i << endl;
	}
private:
	CallbackInterface* m_cb;
};
void testCallback0() {
	Callee0 callee;
	Caller0 caller;
	caller.connectCallback(&callee);
	caller.test();
}
//==================== End Interface class ================

//==================== Function pointer ================

class Callee1 {
public:
	int doWork(int i) {
		cout << "Callee1::doWork() inside callback\n";
		return 2 * i;
	}
};
template<class T>
class Caller1 {
public:
	void connectCallback(T* _cl, int(T::*callback)(int)) {
		this->m_cl = _cl;
		func = callback;
	}
	void test() {
		cout << "Caller1::test() calling callback\n";
		int i = (m_cl->*func)(10);
		cout << "Caller1::test() result: " << i << endl;
	}
private:
	T* m_cl;
	int (T::*func)(int);
};
void testCallback1() {
	Callee1 callee;
	Caller1<Callee1> caller;
	caller.connectCallback(&callee, &Callee1::doWork);
	//caller.connectCallback(bind(&callee,&Callee1::doWork));
	caller.test();
}

//====================End Function pointer ================

//==================== Function object ================
class Callee2 {
public:
	int operator()(int i) {
		cout << "Callee2::doWork() inside callback\n";
		return 2 * i;
	}
};
class Caller2 {
public:
	void connectCallback(Callee2* _callee2) {
		callee2 = _callee2;
	}
	void test() {
		cout << "Caller2::test() calling callback\n";
		int i = (*callee2)(20);
		cout << "Caller2::test() result: " << i << endl;
	}
private:
	Callee2* callee2;
};
void testCallback2() {
	Callee2 callee;

	Caller2 caller;
	caller.connectCallback(&callee);
	caller.test();
}

//====================End Function object ================
//==================== Lambda Function  ================
class Callee3 {
public:
	int doWork(int i) {
		cout << "Callee2::doWork() inside callback\n";
		return 2 * i;
	}
};
class Caller3 {
public:
	void connectCallback(function<int(int)> cb) {
		callback = cb;
	}
	void test() {
		cout << "Caller2::test() calling callback\n";
		int i = callback(20);
		cout << "Caller2::test() result: " << i << endl;
	}
private:
	function<int(int)> callback;
};
void testCallback3() {
	Callee3 callee;

	Caller3 caller;
	caller.connectCallback([&callee](int i) {return callee.doWork(i);});
	caller.test();
}

//====================Lambda Function ================
int main() {
	testCallback3();


	return 0;
}
