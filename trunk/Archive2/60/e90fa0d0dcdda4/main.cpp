#include <iostream>
using namespace std;
class Complex
{
    double real;
    double imaginary;
public:
     Complex();
     Complex(double,double);
     ~Complex();
    void printComplex();
   double getReal();
   double getImaginary();
    void setReal(double);
    void setImaginary(double);
    void addComplex(Complex &);
    void subtractComplex(Complex &);
     };
     
Complex::Complex()
{
    real=imaginary=0;
    }
Complex::Complex(double real, double imaginary)
{
    this->real=real;
    this->imaginary=imaginary;
    }
Complex::~Complex()
{
    }
void Complex::printComplex()
{
    cout<<"the sum is :"<<this->real<<"+"<<this->imaginary<<"i"<<endl;
    cout<<"the difference is :"<<this->real<<"-"<<this->imaginary<<"i"<<endl;
    }
double Complex::getReal()
{
    return real;
    }
double Complex::getImaginary()
{
    return imaginary;
    }
void Complex::setReal(double real)
{
    this->real=real;
    }
void Complex::setImaginary(double imaginary)
{
    this->imaginary=imaginary;
    }
void Complex::addComplex(Complex &comp)
{
    this->real=this->real+comp.real;
    this->imaginary=this->imaginary+comp.imaginary;
    }
void Complex::subtractComplex(Complex &comp)
{
    this->real=this->real-comp.real;
    this->imaginary=this->imaginary-comp.imaginary;
    }
int main()
{
  Complex c1(4.3,5.5),c2();
  
  c2.setReal(2.2);
  c2.setImaginary(2.5);
  c2.getReal();
  c2.getImaginary();
  c1.addComplex(c2);
  c1.subtractComplex(c2);
  c1.printComplex();
  c2.printComplex();
  return 0;
}