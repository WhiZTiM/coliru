#include<iostream>
#include<memory>

using namespace std;

class Test
{
public:
    Test(int a = 0) : m_a(a)
	{
	}
	~Test()
	{
		cout << "Calling destructor" << endl;
	}
public:
	int m_a;
};


//***************************************************************
void Fun(std::unique_ptr<Test> p1)
{
	cout << p1->m_a << endl;
}
//***************************************************************
int  main()
{
	std::unique_ptr<Test> p(new Test(5));
	Fun(std::move(p));
	if (p)
		cout << p->m_a << endl;
	else
		cout << "p is empty";

	return 1;
}