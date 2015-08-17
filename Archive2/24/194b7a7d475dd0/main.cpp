// ConsoleApplication7.cpp : Defines the entry point for the console application.
//
#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;
void displaynum(int numarray[] , int length );
void displaynum(float numarray[], int length);
void putnumbersinavar(int number, int &result);
inline double doublenum(double num);
void area(const double* const pPi,const double* const pRadius, double* const pArea);
void ReadVectorArray(const vector<char>& DynArray);
class Human
{
private:
    string Name;
	int Age;

public:
	void SetName(string HumansName)
	{
		Name = HumansName;
	}

	void SetAge(int HumansAge)
	{
		Age = HumansAge;
	}
	void IntroduceSelf()
	{
		cout << "I am " + Name << " and am ";
		cout << Age << " years old " << endl;
	}
};
int main()
{
	int TNumArr[5] = { 1,2,3,4,5 };
	int *TNumArrP = TNumArr;
	cout << "TNumArrP = 0x" << hex << TNumArrP << endl;
	cout << "TNumArr = 0x" << hex << &TNumArr[0] << endl;
	for (int Index = 0; Index < 5; Index++)
	{
		cout << "Element in pointer array  :" << Index << " = " << *(TNumArrP + Index) << endl;
		cout << "Element in array:" << Index << " = " << TNumArr[Index] << endl;
		cout << "Element in array using pointer syntax : " << Index << " = " << *(TNumArr + Index) << endl;
		cout << "Element in pointer array using array syntax  :" << Index << " = " << TNumArrP[Index] << endl;
	}
	const double Pi = 3.14159265;
	int *pointer = NULL;
	int *tppointer = new int;
	int *incredibly = new int[5];
	vector<char> MyArr;
	MyArr.push_back('w');
	MyArr.push_back('o');
	MyArr.push_back('r');
	MyArr.push_back('l');
	MyArr.push_back('d');
	MyArr.push_back('o');
	MyArr.push_back('f');
	MyArr.push_back('p');
	MyArr.push_back('l');
	MyArr.push_back('a');
	MyArr.push_back('s');
	MyArr.push_back('t');
	MyArr.push_back('i');
	MyArr.push_back('c');
	Human Predator;
	int age = 15;
	Predator.SetAge(age);
	Predator.SetName("Predator");
	Predator.IntroduceSelf();
	int num = 3;
	int result = 0;
	cout << "int num is at" << " 0x" << hex << &num << endl;
	cout << "int result is at" << " 0x" << hex << &result << endl;
	putnumbersinavar(doublenum(num), result);
	pointer = &num;
	string genarray = "yeahdude";
	char* COOLARRAYHERE = new char[9];
	try
	{
		int *texcoords = new(nothrow) int [536870911];
		
		if (texcoords)
		{
			delete[] texcoords;
		}
		else
		{
			cout << "DOWNLOAD MORE RAM!" << endl;
		}
	}
	catch(bad_alloc)
	{
		cout << "Out of Memory for operation" << endl;
	}
	*tppointer = 7;
	*(incredibly + 1) = 5;
	*(incredibly) = 1;
	*(incredibly + 2) = 2;
	*(incredibly + 3) = 3;
	*(incredibly + 4) = 4;
	for (int index = 0; index < 5; index++)
		cout << *(incredibly + index) << endl;
	cout << pointer << endl;
	int& result2 = result;
	const int& result3 = result2;
	cout << result3 << "readonlypls" << endl;
	cout << result << endl;
	cout << "Reference of result" << result2 << hex << &result2 << endl;
	cout << *tppointer << endl;
	pointer = &result;
	cout << pointer << endl;
	cout << *pointer << endl;
	*pointer = 9;
	cout << sizeof(pointer) << endl;
	cout << *pointer << endl;
	ReadVectorArray(MyArr);
	sort(MyArr.begin(), MyArr.end(), \
		[](char Element,char Element2) {return Element2 < Element; });
	ReadVectorArray(MyArr); 
	delete tppointer;
	double Radius = 10.5;
	double Area = 0;
	area(&Pi, &Radius, &Area);
	cout << Area << endl;
	delete[] COOLARRAYHERE;
	delete[] incredibly;
	cout << "GUYZZZ ISNT DELETE COOL" << endl;
    return 0;
}

inline double doublenum(double num)
{
	return num * 2;
}
void ReadVectorArray(const vector<char>& DynArray)
{
	for_each(DynArray.begin(), DynArray.end(), \
		[](char Element) {cout << Element << ""; });
	cout << endl;
}
void area(const double* const pPi, const double* const pRadius, double* const pArea)
{
	if (pPi && pRadius && pArea)
		*pArea = (*pPi) *  (*pRadius) * (*pRadius);
}

/*
void displaynum(int numarray[], int length)
{
	for (int i = 0; i < length; i++)
	{
		cout << numarray[i];
	}
	cout << endl;
}
void displaynum(float numarray[], int length)
{
	for (int i = 0; i < length; i++)
	{
		cout << numarray[i];
	}
	cout << endl;
}
*/

void putnumbersinavar(int number, int &result)
{
	result = number;
}