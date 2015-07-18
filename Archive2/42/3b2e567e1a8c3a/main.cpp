#include <functional>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <bitset>
using namespace std;
using namespace std::placeholders;

class ClassA
{
public:
    void doEvent() {
    	cout << "begin ";
		if (OnEvent1) {
			cout << "-> [has Event1 : " << OnEvent1(1, 2) << "] ";
		} else {
			cout << "-> [no Event1] ";
		}
		if (OnEvent2) {
			cout << "-> [has Event2 : " << OnEvent2(1, 2, 3) << "] ";
		} else {
			cout << "-> [no Event2] ";
		}

		cout << "-> [Event3 : ";
		for (auto v : OnEvent3) {
			cout << v(5) << "/";
		}
		cout << "] ";

		cout << " end" << endl;
	}
	function<int(int, int)> OnEvent1;
	function<string(int, int, int)> OnEvent2;
	vector< function<int(int)> > OnEvent3;
};

class ClassB
{
public:
	ClassA A;
	ClassB(int f, const string &s, bool flag = false): 
		fact(f),
		str(s)
	{
		arr[0] = 7;
		arr[1] = 8;
		arr[2] = 9;
		if (flag) {
			A.OnEvent1 = bind(&ClassB::doEvent1, this, _1, _2);
			A.OnEvent2 = bind(&ClassB::doEvent2, this, _1, _2, _3);
			A.OnEvent3.push_back(bind(&ClassB::doEvent31, this, _1));
			A.OnEvent3.push_back(bind(&ClassB::doEvent32, this, _1));
			A.OnEvent3.push_back(bind(&ClassB::doEvent33, this, _1));
		}
	}
	int doEvent1(int a, int b) {
		return (a + b) * fact;
	}
	string doEvent2(int a, int b, int c) {
		string res = str;
		res += '_' + to_string(a);
		res += '_' + to_string(b);
		res += '_' + to_string(c);
		return res;
	}
	int doEvent31(int a) { return a * arr[0]; };
	int doEvent32(int a) { return a * arr[1]; };
	int doEvent33(int a) { return a * arr[2]; };
private:
	int fact;
	string str;
	int arr[3];
};

void testDelegate()
{
  cout << "----- 测试 delegate -----" << endl;
  ClassB b1(1000, "one");
  b1.A.doEvent();
  b1.A.OnEvent1 = bind(&ClassB::doEvent1, b1, _1, _2);
  b1.A.doEvent();
  b1.A.OnEvent2 = bind(&ClassB::doEvent2, b1, _1, _2, _3);
  b1.A.doEvent();
  ClassB b2(2000, "two", true);
  b2.A.doEvent();

  cout << endl;
}

void testBind()
{
  cout << "----- 测试 bind -----" << endl;
  ClassB b1(1000, "one");
  ClassB b2(1000, "two");

  function<string(ClassB&, int, int, int)> f1;
  f1 = mem_fn(&ClassB::doEvent2);
  cout << "[function] mem_fn -> " << f1(b1, 1, 2, 3) << endl;
  auto f2 = mem_fn(&ClassB::doEvent2);
  cout << "[auto]     mem_fn -> " << f2(b2, 4, 5, 6) << endl;

  function<string(int, int, int)> f3;
  f3 = bind(mem_fn(&ClassB::doEvent2), b1, _1, _2, _3);
  cout << "[function] bind mem_fn -> " << f3(1, 2, 3) << endl;
  auto f4 = bind(mem_fn(&ClassB::doEvent2), b2, _1, _2, _3);
  cout << "[auto]     bind mem_fn -> " << f4(4, 5, 6) << endl;

  function<string(int, int, int)> f5;
  f5 = bind(&ClassB::doEvent2, b1, _1, _2, _3);
  cout << "[function] bind -> " << f5(1, 2, 3) << endl;
  auto f6 = bind(&ClassB::doEvent2, b2, _1, _2, _3);
  cout << "[auto]     bind -> " << f6(4, 5, 6) << endl;

  cout << endl;
}

int main()
{
//  testVector();
//  testMap();
//  testArray();
//  testFunction();
//  testSort();
//  testString();
//  testWstring();
//  testObj();
//  testLibDLL();
//  testLibSLL();
//  testLib();
  //testThread();
  testDelegate();
  testBind();
//  testBitset();

  cin.get(); 
  return 0;
}