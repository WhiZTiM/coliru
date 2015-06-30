#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
using namespace std;

template <class T>
class Matrix
{    
	//Our non member functions.
public:	
    Matrix operator++();
	Matrix operator--();
    Matrix operator++(int); // post increment forms take an int arg
    Matrix operator--(int);

    //........
    void foo() { std::cout << "Compiler warning appeasement" << std::endl; }
    
    //Overloaded increment operator, postfix.
};

template <class T>
Matrix<T> operator++(const Matrix<T> & m, T)
{
    //Iterate through the matrix and add one to each element.
	//Then return the result.
	Matrix<T> current(m.getdimension());
	for (int i = 0; i < m.getdimension(); i++)
	{
		for (int j=0; j < m.getdimension(); j++)
		{
			current.matrixarr[i][j] = m.getnumber(i,j) + 1;
		}
	}
	return current;
}

//Decrement overloaded operator, postfix.
template <class T>
Matrix<T> operator--(const Matrix<T> & m, T)
{
	//Same as increment operator, only subtract one
	//from each element as you iterate through.
	Matrix<T> current(m.getdimension());
	for (int i = 0; i < current.dimension; i++)
	{
		for (int j=0; j < current.dimension; j++)
		{
			current.matrixarr[i][j] = m.getnumber(i,j) - 1;
		}
	}
	return current;

}

int main()
{
    Matrix<int> m;
    m.foo();
}
#endif