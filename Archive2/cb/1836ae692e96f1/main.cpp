#include <iostream>
using namespace std;

class Base
{
protected:
    int count=0;
public:
    Base() { cout << "Constructor called" << endl; }
    ~Base() { cout << "Destructor called" << endl; }
    int getCount() {cout << "The count value is " << count << endl;}
    Base operator ++ (int) {count++;  cout << "Postfix increment called" << endl;}
    Base operator ++ () {count++;  cout << "Prefix increment called" << endl;}
};

class Derived : public Base
{
public:
    Base operator --(int)  {count--;  cout << "Postfix decrement called" << endl;}
};

int main()
{
    Derived A;
    A++;
    ++A;
    A--;
    return 0;
}