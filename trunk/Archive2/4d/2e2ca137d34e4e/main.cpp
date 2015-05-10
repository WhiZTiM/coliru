#include <iostream>    

template<typename T>
class Complex
{
public:

    Complex(T r = 0.0d, T i = 0.0d);

    Complex<T> operator+(const Complex<T>& other);
    Complex<T> operator-(const Complex<T>& other);
    Complex<T> operator*(const Complex<T>& other);

    T magnitude();

    T r, i;
};

int main(int argc, char* argv[])
{
   Complex<double> c;
}