#include <iostream>
struct S
{
    S() { std::cout << "S" << std::endl;  }
	virtual ~S() { std::cout << "~S" << std::endl; }
	double d;
};

struct SS: public S
{
	SS() { std::cout << "SS" << std::endl; }
	virtual ~SS() { std::cout << "~SS" << std::endl; }
	int i;
};

int main()
{
	S* p = new SS[10];
	delete[] p;
	return 0;
}