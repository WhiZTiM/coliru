#include <iostream>
using namespace std;

template <class OwnerType, typename FieldType>
void Test(FieldType (OwnerType::*))
{
    cout << "Field" << endl;	
}

template <class OwnerType, typename FieldType>
void Test(const FieldType (OwnerType::*))
{
	cout << "Const Field" << endl;
}

template <class OwnerType, typename ArgType>
void Test(void (OwnerType::*)(ArgType))
{
	cout << "Method" << endl;
}

struct Example
{
	int field;
	const int constField;
	void method(int) {}
};

int main() 
{
	Test(&Example::method);
}