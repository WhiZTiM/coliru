#include <iostream>

using std::cout;

class Huge 
{
public:
    Huge() { cout << "constructor\n"; }
    Huge(const Huge & h) { cout << "copy\n"; }
    Huge & operator = (const Huge & h) { cout << "assignment\n"; return *this; }
};

class Holder
{
    Huge h;
public:
    Holder(const Huge & h_) : h(h_) {};
};

int main()
{
    Huge bar;
    Holder foo(bar);
}
