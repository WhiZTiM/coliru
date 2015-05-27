#include <iostream>

class Rational { };
const Rational operator*(const Rational& lhs, const Rational& rhs){ return Rational(); }

Rational a, b, c;



int main()
{
    (a * b) = c;
}